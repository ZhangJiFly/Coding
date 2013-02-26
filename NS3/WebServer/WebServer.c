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
#define THREADNUM 5
#define BB 20
#define BUFLEN 8096
#define SHORT 30

//typedef struct thread_pool{
	//pthread_t thread;
	//int connfd;
//} thread_pool;

typedef struct thread_pool{
	pthread_t *thread;
	int connfd;
} thread_pool;


void initthreadpool(thread_pool* threadpool){
	threadpool->connfd = -1;
}

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

void removeport(char host[], char address[]){ //helper functhreadpool[i]tion to remove the port from the recieved host address to check against gethostname()
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
	long size = 0;
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

char* contenttype(char file[]){ // helper function to find the response message based on file type
	char ext[SHORT] = "";
	getExt(file, ext);

	
	if ((strcmp(ext, "html") == 0) || (strcmp(ext, "htm") == 0)){
   		return "text/html";
    }
	else if((strcmp(ext, "jpg") == 0) || (strcmp(ext, "jpeg") == 0)){
    	return "image/jpeg";
    }
	else if(strcmp(ext, "gif") == 0){
    	return "image/gif";
    }
	else if(strcmp(ext, "ico") == 0){
    	return "image/ico";
    }
	else if(strcmp(ext, "css") == 0){
    	return "text/css";
    }
	else{
    	return "application/octet-stream";
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
    long sigpipe;
	char filebuf[BUFLEN];
    long end = -1;
	while (end != 0){
		end = readcontent(filebuf, fd);
		if ((sigpipe = send(connfd, filebuf, sizeof(filebuf), 0)==-1)){
            perror("SIGPIPE");
            break;
        }
		strcpy(filebuf,"");
	}
	fclose(fd);
}

void response(char prot[], char filename[], char address[], int connfd){
	long size = 0;
	int res = 1;
	char sendstr[BUFLEN];
	char responsetype[SHORT] = "";
	char connection[SHORT] = "Connection: open\n";
	char length[SHORT] = "";
	char content[SHORT] = "text/html";
	char contentlong[SHORT] = "";
	char fourohfour[BUFLEN] = "<!doctype html><html>404\nYou are clearly an idiot and no one will ever love you.</html>";
    char fourohoh[BUFLEN] = "<!doctype html><html>400\nYour requests are the shittest requests ive ever seen! Get the fuck out of life! uninstall life lollllll!</html>";
	sscanf(filename, "/%s", filename); //removes the slash from the file name
	res = responsecheck(filename, address);
	
	if (res == 0){
		strcpy(responsetype,"400 Bad Request\n");
        size = strlen(fourohoh);
	}
	if (res == 1){
		strcpy(responsetype,"404 Not Found\n");
		size = strlen(fourohfour);
	}
	if (res == 2){
		strcpy(responsetype,"200 OK\n");
		strcpy(content, contenttype(filename));
		size = filesize(filename);
    }
    sprintf(contentlong, "Content-Type: %s\n", content);
    sprintf(length, "Content-Length: %ld\n", size);
    sprintf(sendstr, "%s %s%s%s%s\n",prot, responsetype, contentlong, connection, length);
    printf("%s", sendstr);
    write(connfd, sendstr, strlen(sendstr));
    if (res == 0){
		write(connfd,fourohoh, strlen(fourohoh));
	}
	if (res == 1){
		write(connfd,fourohfour, strlen(fourohfour));
	}
    if (res == 2){
        cylcicalsend(filename, connfd);
    }
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




void start_threads(thread_pool* threadpool){
	char buf[BUFLEN];
	while (read(threadpool->connfd, buf, BUFLEN)>1){		
		processrequest(buf, threadpool->connfd);
	}
	threadpool->connfd = -1;
	printf("DOES THIS EVER ACTUALLY HAPPEN IF SO MY CODE SHOULDNT WORK");
}

int main(void){
	extern int errno;
	struct sockaddr_in addr;
	struct sockaddr_in cliaddr;
	thread_pool threadpool[THREADNUM];
	int fd,connfd, i;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	socklen_t cliaddrlen = sizeof(cliaddr);
	int set = 1;
	//bbuffer* boundedb;
	//boundedb = createBB();
	fd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(set));
	for (i = 0; i<THREADNUM; i++){
		perror("does this ever print?-1-1-1-1-1-1-1-1-1-1");
		initthreadpool(&threadpool[i]);	
		
	}
	if((bind(fd, (struct sockaddr *)&addr, sizeof(addr))) == -1){
		perror("Port in use, failed to bind");
		return 0;
	}
	listen(fd, 1);
	while(1){
        for (i = 0; i<1; i++){
			if ((&threadpool[i])->connfd == -1){
				perror("does this ever print?222222222222222222");
				connfd = accept(fd, (struct sockaddr *) &cliaddr, &cliaddrlen);
				perror("does this ever print?3333333333333333");
				(&threadpool[i])->connfd = connfd;
				perror("does this ever print?44444444444");
				printf("%d",(&threadpool[i])->connfd);
            	pthread_create((&threadpool[i])->thread, NULL,(void *)start_threads,&threadpool[i]);
				printf("%d", i);
			}
        }
		
	}
	return 0;

}
	
