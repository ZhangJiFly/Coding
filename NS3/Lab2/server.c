#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#define BUFLEN 1500
#define DATE "DATE\r\n"
#define TIME "TIME\r\n"


int main(void)
{
	struct sockaddr_in addr;

	ssize_t rcount;
	char buf[BUFLEN];
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5001);

	int connfd;
	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen = sizeof(cliaddr);

	int fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	bind(fd, (struct sockaddr *)&addr, sizeof(addr));
	listen(fd, 1);
	connfd = accept(fd, (struct sockaddr *) &cliaddr, &cliaddrlen);
	rcount = read(connfd, buf, BUFLEN);
 
	if(strcmp(buf, TIME)==0){
		char *timestr, *sendstr;
		char *countcolon;
		char www[4];
		char dd[3];
		char mmm[4];
		char yyyy[4];
		char time[4];
		int i;
		time_t rawtime;
  		struct tm * timeinfo;
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		timestr = asctime(timeinfo);
		sscanf(timeinfo,"%s %s %s %s %s \n",www,mmm,dd,time,yyyy);
		temp = (strcat(strcat(www, mmm 
		sendstr = strcat(temp, "\r\n");
		write(connfd, sendstr, strlen(sendstr));
	}
	printf(""); // why the fuck are you here? oh wait, does not work with out you!
	if(strcmp(buf, DATE)==0){
		char *timestr, *sendstr;
		char *countcolon;
		char temp[BUFLEN], temp2[BUFLEN];
		int i;
		time_t rawtime;
  		struct tm * timeinfo;
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		timestr = asctime(timeinfo);
		countcolon = strchr(timestr, ':');
		char *p = countcolon-(2*sizeof(char));
		for(; timestr != p ;i++, timestr++){			
			temp[i] = *timestr;
		}
		temp[i++] = '\0';
		char *q = countcolon+(7*sizeof(char));
		for(i = 0; i <5 ;i++, q++){			
			temp2[i] = *q;
		}
		temp2[i++] = '\0';
		printf("%s", temp2);
		strcat(temp, temp2);
		printf("%s", temp);
		sendstr = strcat(temp, "\r\n");
		printf("%s", sendstr);
		write(connfd, sendstr, strlen(sendstr));
	}
	

	close(fd);


	return 0;
}
