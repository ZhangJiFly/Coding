#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeChar( char * string, char letter );

int main(){
	FILE *fp;

	char output[100];

	char name[20];

	char emailAddress[50];

	char ofp[100];

	char fullFile[5000] = "";

	char* position;

	char fullLine[100] = "";

	char fullLine2[100] = "";
	int i;
	fp = fopen("/Users/Crippled.Josh/Coding/RecEmails.csv","r");
	if(fp == NULL){
		perror("Error opening file");

		return(-1);
	}
	
	while (fgets (fullLine,100, fp)) {
		//printf("%s",fullLine);
		if ((position = strchr(fullLine, '<')) != NULL){
			*position = ',';
		}
		if (fullLine[0] == ','){
			for(i = 0; i < strlen( fullLine ); i++ )
   				fullLine[i] = fullLine[i+1];
	
		}
		removeChar(fullLine, '>');
		//strcpy(fullLine2, fullLine);
		strcat(fullFile, fullLine);
		strcpy(fullLine, "");
		}
		printf("%s\n", fullFile);
		return -1;
}



void removeChar( char * string, char letter ) {
	unsigned int i;
  	for(i = 0; i < strlen( string ); i++ )
    	if( string[i] == letter )
      		strcpy( string + i, string + i + 1 );
	
}