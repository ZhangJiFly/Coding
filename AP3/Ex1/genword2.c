#include <stdio.h>
#include <string.h>

int main(){
	int c;
	
	while ((c = getchar()) != EOF){
		while (isalpha(c)){
			putchar(tolower(c));
			c = getchar();
		}
		
		printf("%s", "\n");
	}	
	
	return 0;
}


