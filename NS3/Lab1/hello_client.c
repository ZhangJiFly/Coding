#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#define BUFLEN 1500

int main(int argc, char const *argv[]){
argc=0;
int fd;
	
struct addrinfo hints, *ai, *ai0;
int i;
memset(&hints, 0, sizeof(hints));
hints.ai_family = PF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;

if ((i = getaddrinfo(argv[1], "5000", &hints, &ai0)) != 0) {
    printf("Unable to look up IP address: %s", gai_strerror(i));
}

for (ai = ai0; ai != NULL; ai = ai->ai_next) {
	fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
	if (fd == -1) {
		perror("Unable to create socket");
		continue;
	}
	if (connect(fd, ai->ai_addr, ai->ai_addrlen) == -1) {
		//perror("Unable to connect");
	    close(fd);
        continue;
	}
    
break;
}
if (ai == NULL) {

    // Connection failed, handle the failure...
}
	char data[BUFLEN];
	fgets(data, BUFLEN, stdin);
	int  datalen = strlen(data);
	if (write(fd, data, datalen) == -1) {
    // Error has occurred
 
	}

	return 0;

}
