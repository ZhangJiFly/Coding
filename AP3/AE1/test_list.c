#include <stdio.h>
#include "mentry.h"
#include "mlist.h"

int main(){
	MEntry *me;
	MList *ml;
	int i;
	struct bucket_node *node = NULL;
	me = me_get(stdin);
	ml = ml_create();
	while (me !=NULL){
		ml_add(&ml, me);
		me = me_get(stdin); 
	}
	for (i = 0; i<ml->size; i++){
		node=ml->table[i]->head;
		while ((node = node->next) !=NULL){
			me_print(node->me,stdout);		
		}
	}
	return 0;
}

