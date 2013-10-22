#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
FILE *fp;
char outputLine[100];
char name[20];
char emailAddress[50];
char ofp[100];

fp = fopen("/Users/Crippled.Josh/Desktop/RecEmails.csv","r");
if(fp == NULL){
      perror("Error opening file");
      return(-1);
}

while (fscanf(fp, "%s <%s", name, emailAddress) != EOF) {
  sprintf(outputLine, "%s %s\n", name, emailAddress);
}

return -1;
}
