/** Joshua Marks 1000275m AP3 Exercise 1
This is my own work as defined in the Academic Ethics agreement I
have signed.
*/
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
MList *ml_recreate(int size){	// function to create ml_list with a variable size
	MList *ml;
	int i;

	if (ml_verbose){
		fprintf(stderr, "MList: building mailing list\n");
	}

	if (size<1){
		return 0; 
	}
	
	// invalid table size //
	
	if ((ml = (MList*)malloc(sizeof(MList))) == NULL){
		return 0; // 
	}

	if ((ml->table = (Bucket_LL**)calloc(size, sizeof(Bucket_LL *))) == NULL){  
		return 0; // see above
	}
  

	ml->size = size;
	//Initialize the elements of the table /
	for(i=0; i<ml->size; i++){
		if ((ml->table[i] = (Bucket_LL*)malloc(sizeof(Bucket_LL))) == NULL){ // checks that the heads of all the lists are null			
			return 0;
 
		}

		ml->table[i]->head = (Bucket_Node *)NULL; //casting the head in each bucket as as null. Casting the head in each bucket as as null.
		
	}
	return ml;
}



/* ml_add - adds a new MEntry to the list;
 * returns 1 if successful, 0 if error (malloc)
 * returns 1 if it is a duplicate */

int ml_add(MList **ml, MEntry *me){ // add function to an an element to the hashtable, it is recursive when resizing.
    Bucket_Node *new_node = NULL;
	Bucket_Node *temp = NULL;
	MList *ml1 = *ml;
	MList *ml_bigger;
	MList **ml_bigger_ref = &ml_bigger;
	int i;
    unsigned int hashval = me_hash(me, ml1->size);

	if (ml_verbose){
		fprintf(stderr, "mlist: ml_add() entered\n");
	}
    /* Attempt to allocate memory for list */
    if ((new_node = (Bucket_Node*)malloc(sizeof(struct bucket_node))) == NULL){
		return 0;
	}
    /* Does item already exist? */
	new_node->me = me;
	new_node->next = NULL;
 	
    
	/* item already exists, don't insert it again. */
    if (ml_lookup(ml1, me) != NULL){
		return 1;
	}
    /* If linkedlist has no values already in it, set head to the new node */
	if (ml1->table[hashval]->head == NULL){
		ml1->table[hashval]->head = new_node;
		return 1;
	}
	if (ml1->table[hashval]->size >= SIZE){ // resizing section
		ml_bigger = ml_recreate(ml1->size*2); // make new hashtable of double the size
		for(i=0; i<ml1->size; i++){ // copy over every element from the old table to the new table. 
			for (temp = ml1->table[i]->head; temp != NULL; temp=temp->next){
				ml_add(ml_bigger_ref, temp->me); // recursively call add to put in all the elements
			}
		}
		**ml = *ml_bigger; //set the pointer to the old hashtable pointer to point to the new hashtable pointer
		hashval = me_hash(me, ml_bigger->size); // rehash the node to be added so that it will go into the correct place in the new hashtable
		new_node->next = ml_bigger->table[hashval]->head; // set the new node's next to point to the current head of the bucket/linked list
		ml_bigger->table[hashval]->head = new_node; // move the head to now point at the new node
		ml_bigger->table[hashval]->size++; // increment the size of the bucket
		//ml_destroy(ml1); // Commented out the freeing of the old mlist as descibed in the documentation
		return 1;
	}
	new_node->next = ml1->table[hashval]->head; // set the new node's next to point to the current head of the bucket/linked list 
	ml1->table[hashval]->head = new_node; // move the head to now point at the new node
	ml1->table[hashval]->size++; // increment the size of the bucket/linkedlist
	

    return 1;
}

MList *ml_create(void){ // makes the initial table with a #defined size
	return ml_recreate(HASHSIZE);
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
	
	for (node = ml->table[hashval]->head; node != NULL; node=node->next){ // runs through this bucket/linkedlist seeing if any of the mentries stored are equal to the node being lookedup
		if (me_compare(node->me, me) == 0){
			return node->me;
    	}
	}
    return NULL;

}

/* ml_destroy - destroy the mailing list */
void ml_destroy(MList *ml){ // Not sure if this function is 100% as it seems to work staticly but not dynamically i assume its something to do with my pointer logic in my dynamic section in ml_add()
	int i;
   	Bucket_Node *temp1;

	if (ml_verbose){
		fprintf(stderr, "mlist: ml_destroy() entered\n");
	}    
	if (ml==NULL){
		return;
	}
 
	for(i=0; i<ml->size; i++){ //iterates through table for the buckets/linkedlist

		temp1 = ml->table[i]->head;
		while(temp1 != NULL ){ //interates through the buckets/linkedlists for the nodes
 			Bucket_Node *temp2 = temp1->next;
			//me_print(temp1->me, stdout);
			if (temp1->me != NULL){
				me_destroy(temp1->me); // frees the mentries
			}
			free(temp1); // frees the node 
			temp1 = temp2;

			
		}
		//free(ml->table[i]->head);
		free(ml->table[i]); // frees the linkedlist/bucket
	}

    free(ml->table); // frees the array of linked lists
    free(ml); // frees the table structure
}



