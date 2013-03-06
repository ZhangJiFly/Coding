/* My name is Joshua Marks, my login in 1000275m this is the OS3 Assessed Exercise*/
/* This is my own work except that I have used all of the .o and .h files provided in the StartingFiles most directly the BoundedBuffer*/
#include "freepacketdescriptorstore__full.h"
#include "packetdescriptor.h"
#include "destination.h"
#include "pid.h"
#include "packetdescriptorcreator.h"
#include "freepacketdescriptorstore.h"
#include "pthread.h"
#include "networkdevice.h"
#include "networkdevice__full.h"
#include "BoundedBuffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

NetworkDevice netdev;
BoundedBuffer* incoming;
BoundedBuffer outgoing;
BoundedBuffer buffer;
FreePacketDescriptorStore fpds;
void *getting_thread();
void *sending_thread();
void *buffer_thread();

void init_network_driver(NetworkDevice nd, void *mem_start, unsigned long mem_length, FreePacketDescriptorStore *fpds_ptr){
	pthread_t sendthread;
	pthread_t getthread;
	pthread_t bufferthread;	
	*fpds_ptr = create_fpds();
	fpds = *fpds_ptr;
	int i;
	incoming = malloc(sizeof(BoundedBuffer)*(MAX_PID+1)); // mallocing the space for array of bounded buffers that represent the "cubbyholes" in which packets from the network device will be stored for each process
	for (i = 0; i<=MAX_PID;i++){
		incoming[i] = createBB(3);	
	}
	netdev = nd;
	outgoing = createBB(6); // a bounded buffer that facilitates applications queing up the packets they wish to be sent out.
	buffer = createBB(6); // buffer that gives some wiggle room for recovery if a large flurry of packets arrive.
	create_free_packet_descriptors(fpds, mem_start, mem_length);
	pthread_create(&sendthread, NULL,sending_thread, NULL);
	pthread_create(&getthread, NULL,getting_thread, NULL);
	pthread_create(&bufferthread, NULL,buffer_thread, NULL);
}


void blocking_send_packet(PacketDescriptor pd){//a way for applications to queue up their packets to be sent
	blockingWriteBB(outgoing, pd);
	return;
}

int  nonblocking_send_packet(PacketDescriptor pd){//a way for applications to attempt to queue up their packets to be sent
	return nonblockingWriteBB(outgoing, pd);
}
/* These calls hand in a PacketDescriptor for dispatching */
/* The nonblocking call must return promptly, indicating whether or */
/* not the indicated packet has been accepted by your code          */
/* (it might not be if your internal buffer is full) 1=OK, 0=not OK */
/* The blocking call will usually return promptly, but there may be */
/* a delay while it waits for space in your buffers.                */
/* Neither call should delay until the packet is actually sent      */
void blocking_get_packet(PacketDescriptor* pd, PID pid){ // a way for applications to definitely get packets from their respective "cubbyholes" 
	*pd = blockingReadBB(incoming[pid]);
	return;
}
int  nonblocking_get_packet(PacketDescriptor* pd, PID pid){ //a way for applications to attempt to get packets from their respective "cubbyholes"
	return nonblockingReadBB(incoming[pid], pd);
}
int powers(int a, int b){ // helper function to get a to the power b
	int i;
	if (b = 0){
		return 1;	
	}	
	for (i = 1; i < b; i++){
		a *=a; 
	}
	return a;
}
void *sending_thread(){
	int i;
	PacketDescriptor pd;
	int r; 
	int sleep; 
	while (1){
		pd = blockingReadBB(outgoing);
		for (i=0;i<10;i++){
			if ((send_packet(netdev, pd)) == 1){
				break;			
			}
			r=random();
			sleep = (unsigned int) r; //casting to unsigned removes any negative numbers
			sleep = sleep % powers(2,i); // limits it to the desired range//
			usleep(sleep); //I believe this code is waiting a random time in the range 0-(2 to the power i) microseconds	
		}
		blocking_put_pd(fpds, pd);
	}
	return NULL;
}
void *getting_thread(){
	PacketDescriptor p1, p2;
	blocking_get_pd(fpds, &p1); 
	blocking_get_pd(fpds, &p2); // although these last 2 lines are technically blocking in the receiving thread it is really only initialisation and should in theory never block and if it does is really blocking before everything has started
	init_packet_descriptor(&p1);		
	register_receiving_packetdescriptor(netdev, &p1);
	await_incoming_packet(netdev);
	while (1){
		if (nonblockingWriteBB(buffer, p1)==1){
			if(nonblocking_get_pd(fpds, &p1)==0){
				printf("No packet descriptors left packet dropped\n");
				init_packet_descriptor(&p2);
				register_receiving_packetdescriptor(netdev, &p2);
				while(nonblocking_get_pd(fpds, &p1)==0){
					await_incoming_packet(netdev);
// I think this code means that if there are no packet discriptors left we can at least read from the device into a PacketDescriptor which is then overwritten until a new packet descriptor becomes available this is good because it means that the software is aware that a packet is dropped rather than just the hardware which means that the choice of handling the drop is available. 
				}
			}
			init_packet_descriptor(&p1);
			register_receiving_packetdescriptor(netdev, &p1);
			await_incoming_packet(netdev);
		}
		else{
	// at this stage again the software is aware that a packet is dropped and could potentially handle this if one were so inclined.
		}

	}
	return NULL;
}
void *buffer_thread(){
	PID pid;
	PacketDescriptor p1;
	while(1){
		p1 = blockingReadBB(buffer);
		pid = packet_descriptor_get_pid(&p1);
		blockingWriteBB(incoming[pid], p1);
	}
	return NULL;
}
