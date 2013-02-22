#include <stdio.h>
#include <string.h>
#define IN 0
#define OUT 1
int main(){
	int c;
	int count
	while ((c =getchar()) != EOF)
		if (isalpha(c))
			++count;
			c =getchar();
		while (isalpha(c))
			c=getchar();
		
	}
	printf("%i %s",count,"\n")	
	
	return count;
	}


