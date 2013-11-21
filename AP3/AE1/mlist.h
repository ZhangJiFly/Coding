#ifndef _MLIST_H_
#define _MLIST_H_

#include "mentry.h"

typedef struct orderList OrderList;

extern int ml_verbose;		/* if true, prints diagnostics on stderr */

/* ml_create - created a new mailing list */
MList *ol_create(int size);

/* ml_add - adds a new MEntry to the list;
 * returns 1 if successful, 0 if error (malloc)
 * returns 1 if it is a duplicate */
int ol_add(OrderList *ol, Order *oe);


#endif /* _MLIST_H_ */
