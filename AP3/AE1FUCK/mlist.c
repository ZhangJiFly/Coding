#include "mentry.h"
#include "mlist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 20
#define HASHSIZE 100  

typedef struct bucket_node {
	MEntry *me;
	struct bucket_node *next;
} Bucket_Node;

typedef struct bucket_LL{
	int size;
	Bucket_Node *head;
}Bucket_LL;

struct mlist {
	int size;
	Bucket_LL **table;
};

int ml_verbose = 0;

/* ml_create - created a new mailing list */
MList *ml_create(void){
	MList *ml;
	int i;
	if (ml_verbose){
		fprintf(stderr, "MList: building mailing list\n");
	}
	if (HASHSIZE<1){
		return 0; /* invalid table size */
	}

	if ((ml = (MList*)malloc(sizeof(MList))) == NULL){
		return 0; // 
	}
	printf("========================1\n");
	if ((ml->table = (Bucket_LL**)calloc(HASHSIZE, sizeof(Bucket_LL))) == NULL){  
		return 0; // see above
	}

	ml->size = HASHSIZE;
	/* Initialize the elements of the table */
	printf("========================2\n");
	for(i=0; i<ml->size; i++){
		printf("========================2.1\n");
		if ((ml->table[i]->head = malloc(sizeof(Bucket_Node)* SIZE)) == NULL){ // checks that the heads of all the lists are null
			return 0; 
		}
		ml->table[i]->head = (Bucket_Node *)NULL; //casting the head in each bucket as as null.
	}
	return ml;
}
	
/* ml_add - adds a new MEntry to the list;
 * returns 1 if successful, 0 if error (malloc)
 * returns 1 if it is a duplicate */
int ml_add(MList **ml, MEntry *me){
    Bucket_Node *new_node = NULL;
	MList *ml1 = *ml;
    unsigned int hashval = me_hash(me, ml1->size);
	if (ml_verbose){
		fprintf(stderr, "mlist: ml_add() entered\n");
	}
    /* Attempt to allocate memory for list */
    if ((new_node = (Bucket_Node*)malloc(sizeof(struct bucket_node))) == NULL){
		return 0;
	}
    /* Does item already exist? */
	printf("========================3\n");
	new_node->me = me;
	new_node->next = NULL;
 	
    
	/* item already exists, don't insert it again. */
    if (ml_lookup(ml1, me) != NULL){
		return 1;
	}
    /* Insert into list */

	printf("========================6\n");
	if (ml1->table[hashval]->head == NULL){
		ml1->table[hashval]->head = new_node;
		return 1;
	} 
	new_node->next = ml1->table[hashval]->head;
	ml1->table[hashval]->head = new_node;
	ml1->table[hashval]->size += 1;

    return 1;
}


/* ml_lookup - looks for MEntry in the list, returns matching entry or NULL */
MEntry *ml_lookup(MList *ml, MEntry *me){
    struct bucket_node *node;
    unsigned int hashval = me_hash(me, ml->size);
	if (ml_verbose){
		fprintf(stderr, "mlist: ml_lockup() entered\n");
    }
	/* Go to the correct list based on the hash value, see if me is
     * in the list.  If it is, return return a pointer to the list element.
     * If it isn't, the item isn't in the table, so return NULL. 
     */


	printf("========================4\n");
	for(node = ml->table[hashval]->head; node->next != NULL; node = node->next){
		printf("========================4.1\n");
		if (me_compare(node->me, me) == 0){
			printf("========================4.2\n");
			return node->me;
    	}
		printf("========================5\n");
	}
    return NULL;

}

/* ml_destroy - destroy the mailing list */
void ml_destroy(MList *ml){
	int i;
   	struct bucket_node *temp;
	if (ml_verbose){
		fprintf(stderr, "mlist: ml_destroy() entered\n");
	}    
	if (ml==NULL){
		return;
	}
    //Free the memory for every item in the table, including the 
     //strings themselves.
    
    
    //Free the table itself /
	for(i=0; i<ml->size; i++){
		while ((temp = ml->table[i]->head) !=NULL){
			ml->table[i]->head = ml->table[i]->head->next;
			free(temp->me);
			free(temp->next);			
			free(temp);
			
		}
	}
    free(ml->table);
    free(ml);
}



