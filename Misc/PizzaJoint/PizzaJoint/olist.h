#ifndef _OLIST_H_
#define _OLIST_H_

#include "oentry.h"
typedef struct orderList OrderList;
typedef struct listNode ListNode;

OrderList *orderListCreate();

/* ol_add - adds a new OEntry to the list;
 * returns 1 if successful, 0 if error (malloc)
 * returns 1 if it is a duplicate */
int ol_add(OrderList *ol, Order *oe);

/* the pizza delivery boy actor prints all
 * of the customer id's and their orders */
void pizza_delivery_boy(OrderList *ol);

/* removes the memory allocation for lists of orders
 * returns nothing */
void ldestroy(OrderList *ol);

#endif /* _OLIST_H_ */
