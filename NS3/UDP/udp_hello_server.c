#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#define BUFLEN 1024
#define MESSAGE 1000
#define TIME 10



int main(void)
{
	struct sockaddr_in addr, cliaddr;
	struct ip_mreq imr;

	int fd;
	char buffer[BUFLEN];
	int buflength = sizeof(buffer);
	
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5010);
	
	char temp[BUFLEN];
	socklen_t alen = sizeof(cliaddr);
	int rlen;
	char username[MESSAGE];
	char message[MESSAGE];

	char www[TIME];
	char dd[TIME];
	char mmm[TIME];
	char yyyy[TIME];
	char clock[TIME];

	time_t rawtime;
  	struct tm * timeinfo;
 	

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		perror("Failed to create socket");
	}

	if ((bind(fd, (struct sockaddr *)&addr, sizeof(addr))) == -1){
		perror("Failed to bind socket");
	}
	if (inet_pton(AF_INET, "224.0.0.22", &(imr.imr_multiaddr.s_addr)) == -1){
		perror("Something went wrong in inet_pton");
	}

	if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP,&imr, sizeof(imr)) < 0){
		perror("Unable to join group");
		return -1;
	}
	
	while (1){
		if ((rlen = recvfrom(fd, buffer, buflength, 0,(struct sockaddr *) &cliaddr, &alen)) > 1024){
			printf("Message too large process aborted");
			continue;
		}
		if (strstr(buffer, "FROM") != buffer){
			printf("Message doesnt fit format\n");
			continue;
		}
		if (rlen < 0){
			perror("Reciever Error");
			continue;
		}

		time (&rawtime);
		sscanf(asctime(localtime (&rawtime)),"%s %s %s %s %s",www,mmm,dd,clock,yyyy);
		sprintf(temp, "%s-%s-%s %s - ", dd, mmm, yyyy, clock);

		sscanf(buffer, "FROM%s %[^\n]", username, message);
		printf("%s%s - %s\n", temp, username, message);

	}
	if (setsockopt(fd, IPPROTO_IP, IP_DROP_MEMBERSHIP,&imr, sizeof(imr)) < 0){
		perror("Unable to leave group");
		return -1;
	}



 
	close(fd);


	return 0;
}
