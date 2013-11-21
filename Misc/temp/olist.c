#include "oentry.h"
#include "olist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 

/** a linked list of customers */ 
struct listNode 
{
	Order *oe;
	struct listNode *next;
};
/** contains overall data about the list of customers */
struct orderList
{
	int size;
	ListNode *head;
};


/** instanciates a new order list and allocates memory */

OrderList *orderListCreate()
{
	OrderList *ol;
	/** Return null if memory allocation fails */
	if ((ol = (OrderList*)malloc(sizeof(OrderList))) == NULL)
	{
		return 0; 
	}

    ol->size = 0;
	printf("The address of order list is %p \n", (void*)ol);
    return ol;
	
}

/** function adds an element to the list of orders */

int ol_add(OrderList *ol, Order *oe)
{ 
    int i;
	printf("The address of order list is OL ADD %p \n", (void*)ol);
	printf("The address of order is OL ADD %p \n", (void*)oe);
    ListNode *temp = NULL;
    ListNode *newNode = NULL;
	/** Return null if memory allocation fails */
	printf("adding order? \n");
    if ((newNode = (ListNode*)malloc(sizeof(ListNode))) == NULL)
	{  
        return 0; 
    }
	/** Checks to see if item already exists */
    newNode->oe = oe;
    newNode->next = NULL;
	
	/** If list has no values in it, set head to the new node */
    if ((temp = ol->head) == NULL)
	{
            ol->head = newNode;
            ol->size = ol->size + 1;
    }
	else
	{
		/** Otherwise iterate to the end of the list (first NULL) then set 
		the value at that pointer to be the newNode */
        for (i=0;i<ol->size;i++)
		{
            
            if (temp->next == NULL)
			{
                temp->next = newNode;
                ol->size = ol->size + 1;
                break;
            }
            temp = temp->next;
        }
    }
	printf("managed to add order \n");
    return 1;
}



/** the pizza delivery boy actor prints all 
 of the customer id's and their orders */
void pizza_delivery_boy(OrderList *ol)
{
	/** This is the restaurant menu, order indexes 
	correspond to items on this list */
    const char *menu[7];
    menu[0] = "Pizza Margherita";
    menu[1] = "Pizza Marinara";
    menu[2] = "La Napoletana";
    menu[3] = "Pizza Quattro Stagioni";
    menu[4] = "Pizza ai Quattro Formaggi";
    menu[5] = "Pizza Vegetariana";
    menu[6] = "Pizza alla Bismark";
    int j;
	printf("making list node a temp thing for printing \n");
    ListNode *temp = ol->head;
	printf("list node bit was fine \n");
	printf("The address of order list is PIZZA BOY ol %p \n", (void*)ol);
	printf("The address of order list is PIZZA BOY ol->head %p \n", (void*)ol->head);
	printf("The address of temp is PIZZA BOY temp %p \n", (void*)temp);
	//printf("The address of order is PIZZA BOY ol->head->oe %p \n", (void*)ol->head->oe);
	/** Continues to print until the temp value is null */ 
    while (temp != NULL)
	{
		printf("in the while loop \n");
		printf("The address of PIZZA BOY temp->oe %p \n", (void*)temp->oe);
		/** prints the relevant item from the menu until the 
		order is completely printed */	
		printf("order size bit %d\n", temp->oe->orderSize);
		for (j=0;j<temp->oe->orderSize;j++)
		{
			printf("in the printing for loop \n");
			/** Prints the customer number and their order to the command line */
        	printf("Customer: %d, pizza %d: %s\n", temp->oe->orderId+1, j+1, menu[temp->oe->pizzas[j]]);
        }
		/** moves to the next item in temp */
       	temp = temp->next;
		/** Returns a new line after each customer */
		printf("\n");
    }
}

/** frees all memory allocated for orders using malloc
and calls the odestroy function */
void ldestroy(OrderList *ol)
{
	printf("called l destroy \n");
    int i;
	printf("int i exists \n");
    ListNode *temp1;
	printf("temp 1 exists \n");
    ListNode *temp2 = ol->head;
	printf("temp 2 exits \n");
    for (i=0;i<ol->size;i++)
	{	
		temp1 = temp2->next;
		printf("temp one in for loop \n");
        odestroy(temp2->oe);
		printf("calling o destroy \n");
        free(temp2);
		printf("freeing temp 2 \n");
        temp2 = temp1;
		printf("temp 2 is temp 1 \n");
    }
	printf("freeing ol \n");
    free(ol);
	printf("freed ol \n");
}
