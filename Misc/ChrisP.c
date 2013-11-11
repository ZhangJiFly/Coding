#include <stdio.h>
#include<stdlib.h>

int random_order_generator(int numberofpizzas){
	const char *menu[7];
	menu[0] = "Pizza Margherita";
	menu[1] = "Pizza Marinara";
	menu[2] = "La Napoletana";
	menu[3] = "Pizza Quattro Stagioni";
	menu[4] = "Pizza ai Quattro Formaggi";
	menu[5] = "Pizza Vegetariana";
	menu[6] = "Pizza alla Bismark";
	int pizzaindex[numberofpizzas];
	int i;
	for(i=0; i < numberofpizzas; i++){	
		int randompizzaindex = rand() % 7;
		pizzaindex[i] = randompizzaindex;
		printf("Pizza number %d %s\n",i+1, menu[i]);	
	}
	printf("\n");
	return 0;
}

int main( int argc, char *argv[] ){
	if( argc == 3 ){
		int numberofpizzas = atoi(argv[2]);
		int numberofcustomers = atoi(argv[1]);
		int i;
		for(i = 0; i < numberofcustomers; i++){
			printf("Customer %d ordered:\n", i + 1);
			random_order_generator(numberofpizzas);
		}
    }
    else if( argc < 3 ){
		printf("Too few arguments supplied.\n");
    }
    else{
	}
}