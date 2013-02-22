#include <stdio.h>
#include "mentry.h"

int main(){
	MEntry *me1, *me2;
	int i;
	me1 = me_get(stdin);
	//putting second address into m2
	me2 = me_get(stdin); 
	// putting first address into me1
 	while (me1 != NULL && me2 != NULL && i < 10){
		i++;
		
		/*/print out each component
		printf("surname1: %s\n", me1->surname); 
		printf("house number1: %d\n", me1->house_number);
		printf("postcode1: %s\n", me1->postcode);

		//print full address of me1
		*/me_print(me1, stdout);

		/*/print out hash components and hashval of the first entry
		printf("surname_hash1: %u\n", string_hash(me1->surname));
		printf("postcode_hash1: %u\n", string_hash(me1->postcode));
		printf("me_hash1: %u\n", me_hash(me1, 10));

		/printf("========================1\n");
	
		// print out each component
		printf("surname2: %s\n", me2->surname);
		printf("house number2: %d\n", me2->house_number);
		printf("postcode2: %s\n", me2->postcode);
	
		///print full address of me2
		*/me_print(me2, stdout);
		printf("compare: %d\n", me_compare(me1,me2));
		/*/print out hash components and hashval of the second entry
		printf("surname_hash2: %u\n", string_hash(me2->surname));
		printf("postcode_hash2: %u\n", string_hash(me2->postcode));
		printf("me_hash2: %u\n", me_hash(me2, 10));
		*/
		printf("=========================2\n");
		me_destroy(me1);
		me_destroy(me2);
		me1 = me_get(stdin);
		me2 = me_get(stdin);
	}
	return 0;
}
	
