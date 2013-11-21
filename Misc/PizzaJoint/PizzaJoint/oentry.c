#include "oentry.h"
#include "olist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


//function randomises the pizzas ordered for each customer

int random_order_generator(Order *oe, int numberofpizzas){
	int i;
	int randompizzaindex;
	for(i=0; i < numberofpizzas; i++){
		//the %7 ensures only values between 0-6 (indexes for the menu) are returned
		randompizzaindex = rand() % 7;
		oe->pizzas[i] = randompizzaindex;
	}
	return 0;
}



Order *createOrder(int orderNumber, int id){
	Order *oe;
	if ((oe = (struct order *)malloc(sizeof(struct order))) == NULL) {
        return NULL;
    }
	if ((oe->pizzas = malloc(sizeof(int) * orderNumber)) == NULL) {
		return NULL;
	}
	oe->orderId = id;
	oe->orderSize = orderNumber;
	random_order_generator(oe, orderNumber);
	return oe;
}

void odestroy(Order *oe){
	free(oe->pizzas);
	free(oe);
}

