/*
 * Authors: Peter Dickman and Joe Sventek
 *
 * Simple scheduler implementation
 */

#include "scheduler.h"
#include "TCB.h"
#include "generic_queue.h"
#include "diagnostics.h"

/* Use generic_queue package to provide a simple run-queue */
static GQueue *run_queue;

/* Must keep track of TCB's for current task and idle task */
static TCB * current_taskP;
static TCB * idle_taskP;

void init() {
  /* Initialisation routine */
  /* can be called as often as wished, only does anything first time */

  static int done_init = 0;

  /* check to see if initialisation is complete */
  if (done_init) {
    DIAGNOSTICS("Scheduler: WARNING! Called init routine more than once\n");
  } else {
      /* If not already initialised, ensure no-one else tries to 
       * run init code, create a Q for runnable tasks and a holder
       * for the current task
       *
       * Note that I don't do anything about the idle task here,
       * the scheduler deals with that for itself
       */
      done_init = 1;
      run_queue = create_gqueue();
      idle_taskP = get_idle_task();
      current_taskP = NULL;
      DIAGNOSTICS("Scheduler: Initialised scheduling software\n");
  }
}

void add_runnable_TCB(TCB *t) {
  /* if current task is idle task, save its context and schedule this
     task */
  if (current_taskP == idle_taskP) {
    move_from_CPU_to_TCB(idle_taskP);
    current_taskP = t;
    DIAGNOSTICS("Scheduler: Replaced idle task by newly runnable task\n");
    move_from_TCB_to_CPU(current_taskP);
    return;
  /* simply put the new task at the back of the queue */
  } else if (!gqueue_enqueue(run_queue, t)) {
    DIAGNOSTICS("Scheduler: ERROR! Couldn't add TCB to run_queue\n");
  } else {
    DIAGNOSTICS("Scheduler: Added runnable TCB to scheduler queue\n");
  }
}

void block() {
  /* current task has blocked, so save it then load front task into CPU */
  /* NB Am assuming that scheduler will have been called previously     */
  /* init();   given assumption above, don't need this                  */

  move_from_CPU_to_TCB(current_taskP);
  if (current_taskP != idle_taskP) {
    add_blocked_TCB(current_taskP);
  } else {
    DIAGNOSTICS("Scheduler: Error! Idle task has blocked!\n");
  }

  if (!gqueue_dequeue(run_queue, (void **)&current_taskP)) {
    current_taskP = idle_taskP;
  }
  DIAGNOSTICS("Scheduler: Replacing blocked or terminated task\n");
  /* this is the last thing we do */
  move_from_TCB_to_CPU(current_taskP); 
}

void scheduler() {
  /* what we do depends on whether this is the first time the scheduler
   * is called or not. If not first time just schedule normally, but on
   * first call may have to initialise data structures and don't need
   * to unload the currently running task. Note that the current register, 
   * contents, whatever they are, get discarded on the first call to the scheduler.
   *
   * (In fact the test harness preloads the idle task, so could rely on
   * that, but it isn't a safe (or terribly meaningful) assumption; 
   * not that dropping the current stuff is much better)
   */

  DIAGNOSTICS("Scheduler: Scheduling\n");

  /* Really simplistic, no attempt to do anything except general scheduling */

  /* check to see if this is the first call to the scheduler      */
  /* if it is we don't unload anything                            */
  if (current_taskP != NULL) {
	/* unload the running task, checking to see if it's the idle task */
	move_from_CPU_to_TCB(current_taskP);
	if (current_taskP != idle_taskP) {
	    /* if the task removed from the CPU isn't the idle task we 
	     * add it to the queue, this avoids timeslices being given 
	     * to the idle task unecessarily */
	    if (!gqueue_enqueue(run_queue, current_taskP)) {
	    DIAGNOSTICS("Scheduler: ERROR! Couldn't add TCB to run_queue!\n");
	    }
        }
    }
  /* schedule the task at the front of the queue, if there   */
  /* is one, and the idle task if there's nothing else to do */
  if (!gqueue_dequeue(run_queue, (void **)&current_taskP)) {
    current_taskP = idle_taskP;
  }
  /* Note that this is the last thing we do */
  move_from_TCB_to_CPU(current_taskP);
}

