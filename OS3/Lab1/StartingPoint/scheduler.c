#include "scheduler.h"
#include "TCB.h"
#include "generic_queue.h"
#include "diagnostics.h"


void  init(void){
	GQueue *readyq; 
	readyq = create_gqueue();

}
               /* called once, before any of the others */
void  add_runnable_TCB(TCB *t){
	Qqueue_enqueue(readyq, *t);
	
} /* introduces a runnable TCB into system */
void  block(void){
	GQueue *readyq;
	TCB *t1, *t2;	
	move_from_CPU_to_TCB(t1);
	add_blocked_TCB(t1);
	gqueue_dequeue(ReadyQ, t2);
	move_from_TCB_to_CPU(t2);

}              /* current task has blocked */
void  scheduler(void){
	GQueue *readyq;
	TCB *t1, *t2;	
	move_from_CPU_to_TCB(t1);
	gqueue_dequeue(ReadyQ, t2);
	move_from_TCB_to_CPU(t2);
}          /* timeslice has expired */
