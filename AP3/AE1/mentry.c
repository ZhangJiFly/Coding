#include "mentry.h" 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINE 1000


/* me_get returns the next file entry, or NULL if end of file*/
MEntry *me_get(FILE *fd){
	struct mentry *me;
	char first_line[MAXLINE], second_line[MAXLINE], third_line[MAXLINE], postcode[6];
	int i, j;
	if ((me = (struct mentry *)malloc(sizeof(struct mentry))) == NULL) {
		return NULL;
	}		
		
	if ((me->surname = malloc(sizeof(char) * MAXLINE)) == NULL) {
		return NULL;
	}
	if ((me->postcode = malloc(sizeof(char) * MAXLINE)) == NULL) {
		return NULL;
	}
	if ((me->full_address = malloc(sizeof(char) * (MAXLINE * 3))) == NULL) {
		return NULL;
	}
	
	if (fgets(first_line, MAXLINE, fd) == NULL){
		me_destroy(me);
		return NULL;
	}
	if (fgets(second_line, MAXLINE, fd) == NULL){
		me_destroy(me);
		return NULL;
	}
	if (fgets(third_line, MAXLINE, fd) == NULL){
		me_destroy(me);
		return NULL;
	}

	strcpy(me->full_address,first_line);
	strcat(me->full_address,second_line);
	strcat(me->full_address,third_line); // puts all info into full address

	for (i = 0; first_line[i] != ','; i++){
    		me->surname[i] = (char)tolower(first_line[i]); //puts surname into lower case and into the struct
	}
	me->surname[i++] = '\0';

	me->house_number = strtol(second_line, NULL, 10); // takes housenumber of of the second line and into the struct

	for (i = 0, j = 0; third_line[i] != '\0'; i++){ //puts postcode into uppercase and removes the newline char
    		if (isalnum(third_line[i])){
			postcode[j] = (char)toupper(third_line[i]);
			j++;
			}
	}
	
	strcpy(me->postcode,postcode); //puts postcode into struct
	return me;
	
}

/* me_hash computes a hash of the MEntry, mod size */

unsigned long string_hash(char *string){ // hashing function taking any string and giving it a hashval
	unsigned long hashval;
	for (hashval = 0; *string != '\0'; string++){
		hashval = *string + 43 * hashval;
	}
	return hashval;
}

unsigned long me_hash(MEntry *me, unsigned long size){
	unsigned long hashval = 0;

	hashval = string_hash(me->surname); // putting the hashval from surname into an overall hashval
	hashval = hashval+ string_hash(me->postcode); // adding the postcode hashval to the surname hashval
	hashval = hashval + (unsigned)me->house_number; // adding the housenumber to the hashval
	return hashval % size; 
}	

/* me_print prints the full address on fd */
void me_print(MEntry *me, FILE *fd){

	fprintf(fd, "%s", me->full_address); // prints out all of the full address
}
/* me_compare compares two mail entries, returning <0, 0, >0 if
 * me1<me2, me1==me2, me1>me2
 */
int me_compare(MEntry *me1, MEntry *me2){
	char string1[MAXLINE], string2[MAXLINE];
	sprintf(string1, "%d\n", me1->house_number);
	strcat(string1, me1->surname);
	strcat(string1, me1->postcode);
	sprintf(string2, "%d\n", me2->house_number);
	strcat(string2, me2->surname);
	strcat(string2, me2->postcode);

	return strcmp(string1, string2);

}
/* me_destroy destroys the mail entry
 */
void me_destroy(MEntry *me){
	free(me->surname);
	free(me->postcode);
	free(me->full_address);
	free(me)
;
}


