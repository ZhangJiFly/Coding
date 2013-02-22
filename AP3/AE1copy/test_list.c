#include <stdio.h>
#include "mentry.c"
#include "mlist.c"

int main(){
	struct mentry *me;
	struct mlist *ml;
	int i;
	struct bucket_node *node;
	me = me_get(stdin);
	ml = ml_create(10);
	while (me !=NULL){
		ml_add(ml, me); 
	}
	/*for (i = 0; i<10; i++){
		while ((node=ml->table[i]->next) !=NULL){
			me_print(node->me,"M.out");		
		}
	}*/
return 0;
}

