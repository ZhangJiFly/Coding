#include "oentry.h"
#include "olist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct listNode {
	Order *oe;
	struct listNode *next;
};

struct orderList{
	ListNode *head;
};


//instanciates a new order list and allocates memory

OrderList *orderListCreate(){
	OrderList *ol;
	if ((ol = (OrderList*)malloc(sizeof(OrderList))) == NULL){
		return 0; //
	}
    
    //ol->size = 0;
    
    return ol;
	
}

//function adds an element to the list of orders

int ol_add(OrderList *ol, Order *oe){
    ListNode *temp = NULL;
    ListNode *newNode = NULL;
    if ((newNode = (ListNode*)malloc(sizeof(ListNode))) == NULL){
        return 0;
    }
    newNode->oe = oe;
    newNode->next = NULL;
    if ((temp = ol->head) == NULL){
        ol->head = newNode;
    }else{
        while (temp != NULL){
            
            if (temp->next == NULL){
                temp->next = newNode;
                break;
            }
            temp = temp->next;
            
        }
    }
    return 1;
}



void pizza_delivery_boy(OrderList *ol){
    const char *menu[7];
    menu[0] = "Pizza Margherita";
    menu[1] = "Pizza Marinara";
    menu[2] = "La Napoletana";
    menu[3] = "Pizza Quattro Stagioni";
    menu[4] = "Pizza ai Quattro Formaggi";
    menu[5] = "Pizza Vegetariana";
    menu[6] = "Pizza alla Bismark";
    int i;
    ListNode *temp = ol->head;
    while (temp != NULL){
		for (i=0;i<temp->oe->orderSize;i++){
        	printf("Customer: %d, pizza %d: %s\n", temp->oe->orderId+1, i+1, menu[temp->oe->pizzas[i]]);
        }
        
       	temp = temp->next;
		printf("\n");
    }
}

void ldestroy(OrderList *ol){
    ListNode *temp1;
    ListNode *temp2 = ol->head;
    while (temp2 != NULL){
        temp1 = temp2->next;
        odestroy(temp2->oe);
        free(temp2);
        temp2 = temp1;
    }
    free(ol);
}
