#ifndef _OENTRY_H_
#define _OENTRY_H_

#include <stdio.h>

typedef struct order {
	int orderId;
	int orderSize;
	int *pizzas;
} Order;

/* creates an order for a customer,
 * including customer number, and their pizzas */

int random_order_generator(Order *oe, int numberofpizzas);

Order *createOrder(int orderNumber, int id);

/* removes the memory allocation for lists of orders
 * returns nothing */
void odestroy(Order *oe);

#endif /* _OENTRY_H_ */
