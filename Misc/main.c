#include "oentry.h"
#include "olist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// to compile gcc -W -Wall -o rpd main.c olist.c oentry.c

int main( int argc, char *argv[] ){
	// seed command, makes random numbers different
	// each time by altering the seed based on current time call
	srand(time(0));
	OrderList *ol = orderListCreate();
    
	if( argc == 3 ){
		int numberofpizzas = atoi(argv[2]);
		int numberofcustomers = atoi(argv[1]);
		int i;
		ol = orderListCreate();
		for(i = 0; i < numberofcustomers; i++){
			ol_add(ol, createOrder(numberofpizzas, i));
		}
    }
    else if( argc < 3 ){
		printf("Too few arguments supplied.\n");
    }
    else{
		int j;
		int numberofpizzas;
		for(j = 2; j < argc; j++){
			numberofpizzas = atoi(argv[j]);
			ol_add(ol, createOrder(numberofpizzas, j-2));
		}
    }
    pizza_delivery_boy(ol);
    ldestroy(ol);
    printf("\n");
}