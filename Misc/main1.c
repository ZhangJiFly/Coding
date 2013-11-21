/** Part 2.2 20%

Question 1: How does the algorithm scale when increasing the clients x order matrix size? (10%)

In order to test the computation speed, I have used the libary time.h with the corresponding methods as shown
in the code to time the execution. The results are below:
(Client x Order Matrix)

5 x 5 = 0.0000 (seconds)
10 x 10 = 0.0000 (seconds)
50 x 50 = 0.0100 (seconds)
100 x 100 = 0.0400 (seconds)
1000 x 1000 = 3.1400 (seconds)
5000 x 5000 = Segmentation Error  - Running out of memroy during execution

As you can see from the results above, the computation time increases by the more clients or orders
placed at runtime. The results plotted in a graph (Cannot be shown in the code) show that the results
form an exponentail growth curve, therefore, the time will increase more sharply with the higher inputs.

Question 2: Do you hit a limit at any point (e.g. computational time > than a few minutes for X clients
each with Y pizzas)? (10%)

I eventually hit a limit when requesting greater than 1000 clients with 1000 orders each, this is because
the CPU needs to first calculate the order which increases with the higher values in exponential growth (time).
Along with the computation, the orders need to be printed to the screen which takes a few minutes on top of
the computation. However, if the input is too high, the program recieves a segmentation error, this is due to
running out of memory during execution.

/** Part One 80% - Ordering system for Itailian Restaraunt*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** OrderDetails holds the Pizza(s) order by each client in vairables */
struct OrderDetails
{
    /**currentClient to the number of pizza's */
    char *numPizza;
    /** Left and Right currentClient to hold orders placed,
        which can be traversed through (linked lists) */
    char **pizzaOrder;
};

/**ClientDetails holds all information needed for the order in vairables */
struct ClientDetails
{
    /**Unique client number to determine orders */
    int clientID;
    /**Combines the two structures to form a linked list */
    struct OrderDetails Order;
    /**currentClient which traverses through the list */
    struct ClientDetails *next;
};
/**All vairables in ClientDetails can be called from client**/
typedef struct ClientDetails client;

/**Generates a random number */
int rand(void);
char *menu[7];

/**Function that holds an array filled with the 7 Pizzas available
    which is called at each order. It returns a random pizza each time
    its called */
char* randomPizza (int n)
{
	menu[0] = "MARGHERITA";
	menu[1] = "VEGETARIANA";
	menu[2] = "CALZONE";
	menu[3] = "NAPOLETANA";
	menu[4] = "QUATTRO STAGIONI";
	menu[5] = "CAPRICCIOSA";
	menu[6] = "MARINARA";
	return menu[n];
}

/**Argc contains the number of arguments and argv
    contains the order details */
int main (int argc, char *argv[])
{
    clock_t start = clock() ;

    /**Hold the number of clients, which is the 1st parameter,
        atoi is used to convert a char to int*/
    int queueSize = atoi(argv[1]);
    /**Points to the rooting currentClient to the address in memory*/
    client *root;
    /**Points to the current address in memory */
    client *currentClient;
    /**Allocates a block of memory to the size of client*/
    root = malloc(sizeof(client));
    /**Once allocated, returns to root currentClient*/
    currentClient = root;
    /**Initializes the number of clients (Atleast one)*/
    int clientNum = 1;

    /** Handles if the clients order the same amount of pizzas*/
    if (argc == 3)
    {
        int y;
        for (y = 2; y < queueSize + 2; y++)
        {
            argv[y] = argv[2];
        }
    }
    /**intializes the random generator */
    srand(time(0));
    int i, x;
    /**The for loop updates all the currentClients used in the linked list to the next
        client with their order. */
    for (i=2; i<(queueSize + 2); i++)
    {
        /**Allocates memory to the next node for client*/
        (*currentClient).next = malloc(sizeof(client));
        (*currentClient).Order.numPizza = argv[i];
        (*currentClient).clientID = clientNum;
        /**sets the currentClient reference to the dynamic memory of pizzas ordered */
        (*currentClient).Order.pizzaOrder = malloc(atoi((*currentClient).Order.numPizza)* sizeof(char *));
        /**For each pizza order, a random pizza is assinged to each order currentClient */
        for (x =0; x < atoi((*currentClient).Order.numPizza); x++)
        {
            (*currentClient).Order.pizzaOrder[x] = randomPizza((rand()%7));
        }
        /**currentClients points to the next in the list*/
        currentClient = (*currentClient).next;
        /**Increments the client number */
        clientNum++;
    }
    printf("\n");
    /**Keeps pointing to zero until it reaches the end of the list*/
    (*currentClient).next = 0;
    currentClient = root;


        while ((*currentClient).next != 0)
        {
            printf("\n");
            /** Print the a unique client ID with the corresponding order */
            printf("Client %d orders %s pizza(s)",(*currentClient).clientID,(*currentClient).Order.numPizza);
            for (x=0; x<atoi((*currentClient).Order.numPizza); x++)
            {
               printf("\n\tPizza: ");
               /** Print the type of the pizza*/
               printf("%s",(*currentClient).Order.pizzaOrder[x]);
            }
            free((*currentClient).Order.pizzaOrder);
            printf("\n");
            /**Recursively points the currentClient to the next in the list*/
        currentClient = (*currentClient).next;
        }
    free(currentClient);
    free(root);
    clock_t end = clock() ;
    double CPU_Time = (end-start)/(double)CLOCKS_PER_SEC;
    printf("string %f\n", CPU_Time);
}

