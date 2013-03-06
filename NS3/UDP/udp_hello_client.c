#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#define BUFLEN 1000

int main(int argc, char const *argv[]){

	int fd;
	char buffer[BUFLEN];
	struct sockaddr_in addr;
	char *username;
	char finalmessage[1024]; 
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
   	addr.sin_port = htons(5010);
    	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	username = getlogin();

	if (argc < 2){
		printf("Not enough arguments, message aborted.\n");
		return -1;
	}
	if (sizeof(argv[1]) > 1000){
		printf("Message too large process abortedzn");
	}
	

	if((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
		perror("Failed to create socket");
	}

	inet_pton(AF_INET, "224.0.0.22", &addr.sin_addr.s_addr);
	
	strcpy(buffer, argv[1]);
	sprintf(finalmessage, "FROM 1005851j\n%s\n", buffer); 
	printf(finalmessage);
	if (sendto(fd, finalmessage, sizeof(finalmessage), 0, (struct sockaddr *) &addr, sizeof(addr)) == -1){
		perror("Failed to send");
	}

	return 0;

}

