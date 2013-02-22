#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <pthread.h>
#define THREADNUM 1
#define BB 20
#define BUFLEN 8096
#define SHORT 30
int readline(char line[], char buf[], int i){ //turns the read input from the browser into individual lines which is just easier to deal with.
	int k;
	for (k= 0; buf[i] != '\r'; i++, k++){
		line[k] = buf[i];
	}
	line[k] = '\r';
	line[k+1] = '\n';
	line[k+2] = '\0';
	return i+2;
}

long readcontent(char filebuf[], FILE *fd){ // puts up to BUFLEN characters in a file into a buffer
	long end = -1;
	if (fd != NULL){
		end = fread(filebuf, BUFLEN, 1, fd);
	}
	return end;
}

void removeport(char host[], char address[]){ //helper function to remove the port from the recieved host address to check against gethostname()
	size_t subsize;
	subsize = strcspn(host, ":");
	strncpy(address, host, subsize);
}

void getExt (char file[], char ext[]) { //simple helper function to get the file extension
	char *pointer;
	pointer = strrchr (file, '.');
	strcpy(ext, pointer+1);
    if (ext == NULL){
        ext = ""; 
	}
}
long filesize(char filename[]){ //helper function to obtain filesize
	long size;
	struct stat st;
	stat(filename, &st);
	size = st.st_size;
	return size;
}

int hostnamecheck(char address[]){ // checks that the hostname matches gethostname()
	char hostname[BUFLEN];
	size_t size = strlen(hostname);
	gethostname(hostname, size);
	char local[] = "localhost";
	char dcssuf[] = ".dcs.gla.ac.uk";

	if (strcmp(local, address) == 0){
		return 1;
	}
	if (strcmp(hostname,address) == 0){
		return 1;
	}
	strcat(hostname, dcssuf);
	if (strcmp(hostname, address) == 0){
		return 1;
	}
	return 0;
}

long getinputs(char buf[], char method[] ,char file[] ,char prot[] ,char host[]){
//obtains the the different sections of the headers required for later use
	int i = 0;
	int linecount = 0;
	char line[BUFLEN] = "";

	while (strcmp(line, "\r\n") != 0){
		i = readline(line, buf, i);
		linecount++;
		if (linecount == 1){
			sscanf(line,"%s %s %s\r\n",method, file, prot);
		}
		sscanf(line,"Host: %s",host);
		printf("%s", line);
	}
	return strlen(buf);
}

void contenttype(char file[], char content[]){ // helper function to find the response message based on file type
	char ext[SHORT] = "";
	getExt(file, ext);

	if (strcmp(ext, "html") == 0){
   		strcpy (content, "text/html");
    }
	if(strcmp(ext, "jpg") == 0){
    	strcpy (content, "image/jpeg");
    }
	if(strcmp(ext, "gif") == 0){
    	strcpy (content, "image/gif");
    }
	if(strcmp(ext, "ico") == 0){
    	strcpy (content, "image/ico");
    }
	if(strcmp(ext, "css") == 0){
    	strcpy (content, "text/css");
    } 
}

int responsecheck(char file[], char address[]){//determins what kind of response is sent e.g. 200 OK, 404 Not Fount etc.
	FILE *fd;
	int hostcheck;
	hostcheck = hostnamecheck(address);
	if (!hostcheck){
		return 0;
	}
	fd = fopen(file, "r");
	printf("%s\n", file);
	
	if (fd == NULL){
		return 1;
	}
	fclose(fd);
	return 2;
}

void cylcicalsend(char filename[], int connfd){
	FILE *fd;	
	fd = fopen(filename, "r");
	char filebuf[BUFLEN];
    	int end = -1;
	while (end != 0){
		end = readcontent(filebuf, fd);
		send(connfd, filebuf, sizeof(filebuf), 0);
		strcpy(filebuf,"");
	}
	fclose(fd);
}

void response(char prot[], char filename[], char address[], int connfd){
	long size;
	int res;
	char sendstr[BUFLEN];
	char responsetype[SHORT] = "";
	char connection[SHORT] = "Connection: open\n";
	char length[SHORT] = "";
	char content[SHORT] = "html/index";
	char contentlong[SHORT] = "";
	
	sscanf(filename, "/%s", filename); //removes the slash from the file name
	res = responsecheck(filename, address);
	size = filesize(filename);
	
	if (res == 0){
		strcpy(responsetype,"400 Bad Request\n");
		strcpy(filename, "404.html");
		size = filesize("400.html");
	}
	if (res == 1){
		strcpy(responsetype,"404 Not Found\n");
		strcpy(filename, "404.html");
		size = filesize("404.html");
	}
	if (res == 2){
		strcpy(responsetype,"200 OK\n");
		contenttype(filename, content);
		size = filesize(filename);
	}
    
	sprintf(contentlong, "Content-Type: %s\n", content);
	sprintf(length, "Content-Length: %ld\n", size);
	sprintf(sendstr, "%s %s%s%s%s\n",prot, responsetype, contentlong, connection, length);
	printf("%s", sendstr);
	write(connfd, sendstr, strlen(sendstr));
    	cylcicalsend(filename, connfd);	
	write(connfd, "\r\n", strlen("\r\n"));
}

void processrequest(char buf[], int connfd){
	char method[BUFLEN] = "";
	char file[BUFLEN] = "";
	char host[BUFLEN] = "";
	char prot[BUFLEN] = "";
	char address[BUFLEN] = "";
	ssize_t rcount = 0;
    
	while (strstr(buf, "\r\n\r\n") == NULL){
		rcount = read(connfd, buf, BUFLEN);
	}
	getinputs(buf, method, file, prot, host);
	removeport(host, address);
	response(prot, file, address, connfd);
}

/*bbuffer* createBB(){
	bbuffer* bb = malloc(sizeof(bbuffer));
	pthread_mutex_init(&bb->bblock, NULL);
	pthread_cond_init(&bb->non->non_full, NULL);
	pthread_cond_init(&bb->non->non_empty, NULL);
	bb->bbsize = BB;
	bb->currentRead = 0;
	bb->currentWrite = 0;
	bb->isEmpty = 1;
	bb->connections = malloc(sizeof(void *)*BB);
}*/

void start_threads(int connfd){
	char buf[BUFLEN] = "";
	while (read(connfd, buf, BUFLEN)>1){
		processrequest(buf, connfd);
	}
}

int main(void){
	extern int errno;
	struct sockaddr_in addr;
	struct sockaddr_in cliaddr;
	int fd, connfd;// i;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	socklen_t cliaddrlen = sizeof(cliaddr);
	int set = 1;
	//bbuffer* boundedb;
	//pthread_t *threads = malloc(sizeof(pthread_t)*THREADNUM);
	//boundedb = createBB();
	fd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(set));

	if((bind(fd, (struct sockaddr *)&addr, sizeof(addr))) == -1){
		perror("Port in use, failed to bind");
		return 0;
	}
	listen(fd, 1);
	while(1){
		connfd = accept(fd, (struct sockaddr *) &cliaddr, &cliaddrlen);
		start_threads(connfd);
	
	}
	return connfd;
}
	
