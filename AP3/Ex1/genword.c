#include <stdio.h>
#include <string.h>

int main(){
	int c;
	
	while ((c = getchar()) != EOF){
		while (isalpha(c)){
			putchar(c);
			c = getchar();
		}
		
		if (c!= "\n"){
			printf("%s", "\n");
		}
	}	
	
	return 0;
}


