#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int readline(char line[], int max)
{
	if (fgets(line, max, stdin) == NULL)
		return 0;
	else
		return strlen(line);
}

int writeline(const char line[])
{
	fputs(line, stdout);
	return strlen(line);
}

int main() {
	char line[MAXLINE];
	while ((readline(line, MAXLINE)) > 0)
		writeline(line);
		
	return 0;

}
