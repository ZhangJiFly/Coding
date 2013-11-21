#include "oentry.h"
#include "olist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/** function randomises the pizzas ordered for each customer */

int random_order_generator(Order *oe, int numberofpizzas)
{
	int i;
	int randompizzaindex;
	/** Iterates over the number of pizzas ordered and adds them to the order for each customer */
	for(i=0; i < numberofpizzas; i++)
	{	
		/** the %7 ensures only values between 0-6 (indexes for the menu) are returned */
		randompizzaindex = rand() % 7;
		oe->pizzas[i] = randompizzaindex;
	}
	printf("order size in create order print bit %d\n", oe->orderSize);
	return 0;
}

/** Allocates memory for a single customers order, 
first the initial struct then the pizza array inside the stuct */

Order *createOrder(int orderNumber, int id)
{
	Order *oe;
	/** Return null if memory allocation fails */
	if ((oe = (struct order *)malloc(sizeof(struct order))) == NULL) 
	{
			return NULL;
	}		
	/** Return null if memory allocation fails */
	if ((oe->pizzas = malloc(sizeof(int) * orderNumber)) == NULL) 
	{
		return NULL;
	}
	/** assigns relevant properties to the order, such as order number and size */
	oe->orderId = id;
	oe->orderSize = orderNumber;
	printf("order size in create order %d\n", oe->orderSize);
	/** calls function to randomly generate menu indexes */
	random_order_generator(oe, orderNumber);
	printf("created an order properly\n");
	return oe;
}

/** frees all memory allocated for orders using malloc */
void odestroy(Order *oe){
	free(oe->pizzas);
	printf("free works for oe-> pizzas \n");
	free(oe);
	printf("free works for oe \n");
}

