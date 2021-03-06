#ifndef __GENERIC_QUEUE
#define __GENERIC_QUEUE

/*
 * Authors:    Peter Dickman and Joe Sventek
 *
 * Generic package for a queue (can add at rear and remove from front)
 */

/*
 * packages which use this queue simply see GQueues,
 * the queues simply hold GQueueElements
 *
 * two way decoupling encourages information hiding
 */

typedef struct gqueue GQueue;
typedef void *GQueueElement;

/********************************/
/* Constructors and Destructors */
/********************************/

/*
 * can create and destroy empty GQueues
 * create returns NULL if unsuccessful, GQueue * if successful
 * destroy returns 1 if successful, 0 if unsuccessful
 */

GQueue *create_gqueue (void); 
int destroy_gqueue(GQueue *gq);

/***********/
/* Methods */
/***********/

/* Can add to rear of queue and remove from front */
/* in each case return true if successful, false if not   */

int gqueue_enqueue (GQueue *gq, GQueueElement gqe);

/* 
 * Note that the dequeue function puts its result in the place indicated
 * by the second argument, rather than returning it. This allows the use
 * of a success code as result, simplifying the use of the function in
 * code that checks carefully for any problems that might arise.
 */
int gqueue_dequeue (GQueue *gq, GQueueElement *gqep);

/* Can also find out how long a queue currently is */

unsigned long gqueue_length(GQueue *gq);

/*
 * can also discard queue contents
 */
void gqueue_purge(GQueue *gq);

/********************/
/* Advanced Methods */
/********************/

/*---------------------------------------------------------*/
/* map applies the function provided as second arg to each */
/* value stored in the queue in turn, from front to rear.   */
/* Note that the function whose address is passed must     */
/* take a GQueueElement as argument and return nothing.    */

void gqueue_map(GQueue *gq, void (*fp)(GQueueElement gqe));

/*------------------------------------------------------------*/
/* discards queue contents having applied cleaner routine to   */
/* each of the stored items in turn; cleaner should free them */

void gqueue_purge_carefully (GQueue *gq, void (*cleaner)(GQueueElement gqe));
#endif	/* __GENERIC_QUEUE */
