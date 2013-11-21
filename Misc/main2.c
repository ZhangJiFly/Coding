#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** CustomerOrder holds the Pizza(s) order by each customer in vairables */
typedef struct CustomerOrder
{
    /**currentCustomer to the number of pizza's */
    int orderSize;
    /** Left and Right currentCustomer to hold orders placed,
        which can be traversed through (linked lists) */
    int *pizzaOrdered;
} order;

/**CustomerDetails holds all information needed for the order in vairables */
typedef struct CustomerDetails
{
    /**Unique customer number to determine orders */
    int customerID;
    /**Combines the two structures to form a linked list */
    struct CustomerOrder *Order;
    /**currentCustomer which traverses through the list */
    struct CustomerDetails *next;
}customer;

/**Generates a random number */
int random_index_generator()
{
    return rand() % 7;
}

/**Function that holds an array filled with the 7 Pizzas available
    which is called at each order. It returns a random pizza each time
    its called */
char *menu[7];
char* random_pizza_generator(int index)
{
    char *menu[7];
    menu[0] = "Pizza Margherita";
    menu[1] = "Pizza Marinara";
    menu[2] = "La Napoletana";
    menu[3] = "Pizza Quattro Stagioni";
    menu[4] = "Pizza ai Quattro Formaggi";
    menu[5] = "Pizza Vegetariana";
    menu[6] = "Pizza alla Bismark";
	return menu[index];
}

void pizza_boy(customer *root){
    customer *currentCustomer = root;
    customer *temp;
    while (currentCustomer->next != NULL)
        {
            int i;
            printf("\n");
            printf("customer %d orders %d pizza(s)",currentCustomer->customerID,currentCustomer->Order->orderSize);
            for (i=0; i<currentCustomer->Order->orderSize; i++)
            {
               printf("\n\tPizza: ");
               printf("%s",random_pizza_generator(currentCustomer->Order->pizzaOrdered[i]));
            }
            temp = currentCustomer->next;
            free(currentCustomer->Order->pizzaOrdered);
            free(currentCustomer->Order);
            free(currentCustomer);
            currentCustomer = temp;
            printf("\n");
            
        }
    //free(currentCustomer->Order->pizzaOrdered);
    //free(currentCustomer->Order);
    //free(currentCustomer);
}

int main (int argc, char *argv[])
{
    srand(time(NULL));
    int queuelength = atoi(argv[1]);
    customer *root;
    customer *currentCustomer;
    root = malloc(sizeof(customer));

    currentCustomer = root;
    int customernumber = 1;  
    printf("%d\n", argc);
    printf("%d\n", queuelength);
    if (argc < 3)
    {
        printf("Too few arguments supplied. Usage: ./rpd int int\n");
    }
    else if (argc == 3)
    {
        int i,j;
        for (i=2; i<(queuelength + 2); i++, customernumber++)
        {
            if ((currentCustomer->next = malloc(sizeof(customer))) == NULL)
            {
                return NULL;
            }
            if ((currentCustomer->Order = malloc(sizeof(order))) == NULL)
            {
                return NULL;
            }

            currentCustomer->Order->orderSize = atoi(argv[2]);
            currentCustomer->customerID = customernumber;
            if ((currentCustomer->Order->pizzaOrdered = malloc(currentCustomer->Order->orderSize*sizeof(int))) == NULL)
            {
                return NULL;
            }
            for (j =0; j < currentCustomer->Order->orderSize; j++)
            {
                currentCustomer->Order->pizzaOrdered[j] = random_index_generator();
            }
            currentCustomer = currentCustomer->next;
        }
    }
    else if((argc-2) == queuelength)
    {
        int i, j;
        for (i=2; i<queuelength + 2; i++, customernumber++)
        {
            currentCustomer->next = malloc(sizeof(customer));
            currentCustomer->Order = malloc(sizeof(order));
            currentCustomer->Order->orderSize = atoi(argv[i]);
            currentCustomer->Order->pizzaOrdered = malloc(currentCustomer->Order->orderSize * sizeof(int));
            currentCustomer->customerID = customernumber;
            for (j =0; j < currentCustomer->Order->orderSize; j++)
            {
                currentCustomer->Order->pizzaOrdered[j] = random_index_generator();
            }
            currentCustomer = currentCustomer->next;
        }
    }
    else{
        printf("Numbder of customers argument does not match your input try inputting the first argument then placing that many further args like '2 2 3' not '3 2 1' \n");
    }
    currentCustomer->next = NULL;

    pizza_boy(root);
}


