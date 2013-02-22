#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#define BUFLEN 1500


int main(void)
{
	struct sockaddr_in addr;

	ssize_t i;
	ssize_t rcount;
	char buf[BUFLEN];
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family      = AF_INET;
	addr.sin_port        = htons(5000);

	int connfd;
	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen = sizeof(cliaddr);

	int fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);

	bind(fd, (struct sockaddr *)&addr, sizeof(addr));
	listen(fd, 1);
	connfd = accept(fd, (struct sockaddr *) &cliaddr, &cliaddrlen);
	rcount = read(connfd, buf, BUFLEN);
	for (i = 0; i < rcount; i++) {
		printf("%c", buf[i]);
	}

	close(fd);


	return 0;
}
