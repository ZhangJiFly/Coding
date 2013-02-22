#include "mentry.h"
#include "mlist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 20  

typedef struct bucket_node {
MEntry *me;
struct bucket_node *next;
} Bucket_Node;

struct mlist {
int size;
Bucket_Node **table;
};

extern int ml_verbose =0;

/* ml_create - created a new mailing list */
MList *ml_create(void){
    MList *ml;
	Bucket_Node *bn;
	//int i;
	if (ml_verbose)
		fprintf(stderr, "mlist: creating mailing list\n");
	if (SIZE<1){
		return 0; /* invalid size for table */
	}
    if ((ml = malloc(sizeof(struct mlist))) == NULL){
		return 0;
	}
    if ((bn = malloc(sizeof(struct bucket_node)*SIZE)) == NULL){
		return 0;
	}
	ml->size = SIZE;
  	/* Initialize the elements of the table */
    /*for(i=0; i<hash_size; i++){ 
		ml->table[i] = NULL;
		ml->table[i]->me = NULL;
		ml->table[i]->next = NULL;
	}*/


    return ml;
}
	
/* ml_add - adds a new MEntry to the list;
 * returns 1 if successful, 0 if error (malloc)
 * returns 1 if it is a duplicate */
int ml_add(MList **ml, MEntry *me){
    Bucket_Node *new_node;
    Bucket_Node *current_node;
	MList *ml1 = *ml;
    unsigned int hashval = me_hash(me, ml1->size);
	if (ml_verbose)
		fprintf(stderr, "mlist: ml_add() entered\n");
    /* Attempt to allocate memory for list */
    if ((new_node = malloc(sizeof(struct bucket_node))) == NULL){
		return 0;
	}
	//new_node->me = NULL;
	//new_node->next = NULL;
    /* Does item already exist? */
    current_node->me = ml_lookup(ml1, me);
    
	/* item already exists, don't insert it again. */
    if (current_node != NULL){
		return 1;
	}
    /* Insert into list */
	new_node->me = me;
	new_node->next = NULL;
	current_node = ml1->table[hashval];
	while ((current_node = current_node->next) != NULL){
		}
	current_node->next = new_node;
	new_node->me = me;
    return 1;
}


/* ml_lookup - looks for MEntry in the list, returns matching entry or NULL */
MEntry *ml_lookup(MList *ml, MEntry *me){
    struct bucket_node *node;
    unsigned int hashval = me_hash(me, ml->size);
	if (ml_verbose)
		fprintf(stderr, "mlist: ml_lockup() entered\n");
    /* Go to the correct list based on the hash value and see if str is
     * in the list.  If it is, return return a pointer to the list element.
     * If it isn't, the item isn't in the table, so return NULL. 
     */

    node = ml->table[hashval];
	while ((node=node->next) !=NULL){
		if (me_compare(node->me, me) == 0){
			return node->me;
    	}
	}
    return NULL;

}

/* ml_destroy - destroy the mailing list */
void ml_destroy(MList *ml){
	int i;
    struct bucket_node *temp;
	if (ml_verbose)
		fprintf(stderr, "mlist: ml_destroy() entered\n");
    if (ml==NULL){
		return;
	}
    /* Free the memory for every item in the table, including the 
     * strings themselves.
     */
    
    /* Free the table itself */
	for(i=0; i<ml->size; i++){
		while ((temp = ml->table[i]->next) !=NULL){
			free(temp->me);
			free(temp->next);			
			free(temp);
			
		}
	}
    free(ml->table);
    free(ml);
}



