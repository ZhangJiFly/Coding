#include "oentry.h"
#include "olist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/** to compile gcc -W -Wall -o rpd main.c olist.c oentry.c */

/** 
Assesment questions: 

Question 1: 

As you can see from the data below, as the customer*pizza matrix increases, the time taken to complete the computation also increases. Plotting this data (not shown here) would illustrate exponential growth. 

Customers/Pizzas	Time (s)
	5				0.000178
	50				0.007033
	100				0.023931
	200				0.095663
	300				0.206343
	400				0.370277
	500				0.571995

Question 2:

After trying the example of 100,000 customers ordering 1000,000 pizzas the program crashed. While the actual limit may be before this, the experiment has clearly demonstrated that the system does reach a limit at some point. The reason for this is that the system runs out of memory, and it can no longer allocate any more memory for the program to store the new pizza orders being created so the system crashes.   

*/

int main( int argc, char *argv[] ){
	/** clock used for timing system, used for testing efficiency */
//	clock_t begin, end;
//	double time_spent;
//	begin = clock();
	/** seed command, makes random numbers different 
	each time by altering the seed based on current time call */
	srand(time(0));
	OrderList *ol = NULL;	
	/** determines if there are 3 arguments, and if so, assumes all 
	order sizes are the same as the third argument */
	if (argc == 3)
	{
		printf("3 args function \n");
		printf("3 args number of pizzas \n");
		int numberofpizzas = atoi(argv[2]);
		printf("3 number of customers \n");
		int numberofcustomers = atoi(argv[1]);
		int i;
		printf("3 creating order list \n");
		ol = orderListCreate();
		for (i = 0; i < numberofcustomers; i++)
		{	
			printf("3 args adding order \n");
			ol_add(ol, createOrder(numberofpizzas, i));
		}
    }
	/** Informs user if too few arguments have been supplied
	instructs on usage */
    else if (argc < 3)
	{
		printf("Too few arguments supplied. Usage: ./rpd int int\n");
    }
	else
	{
		/** Processes a queue of customers where each order is a 
		different size */
		int j;
		int numberofpizzas;
		ol = orderListCreate();
		/** Iterates over the arguments, starting after queue size */
		for (j = 2; j < argc; j++)
		{
			numberofpizzas = atoi(argv[j]);
			ol_add(ol, createOrder(numberofpizzas, j-2));
		}
	}
	/** Calls pizza delivery function and prints the orders to the command line */
    pizza_delivery_boy(ol);
	printf("print function called \n");
	/** Calls a function that deallocates memory used with the malloc function */
	printf("calling ldestroy \n");
    ldestroy(ol);
	printf("destroy worked \n");
	/** once program finished, stop timer */
//	end = clock();
//	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	/** prints the time for analysis, by default, commented to hide from end user */
//	printf("The program took %lf seconds to complete\n", time_spent);

	return 0;
}