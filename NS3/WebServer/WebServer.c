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
#define THREADNUM 10
#define BB 20
#define BUFLEN 8096
#define SHORT 30

typedef struct thread_pool{
	pthread_t *thread;
	ssize_t connfd;
} thread_pool; //struct so that each thread can have its own changeable connfd (everyone else says stuff about mutexs but i cant figure out why i need them.... unless thats how I get it to not busy wait... but who cares enough...


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
	return i+2; // this function is not needed at all it just helped me to think about how everything was working when i started the project. 
}
//My method abstraction might have got a bit out of control but when i did this originally it was bigger and some of the functionality had to be ported to other methods and now it looks a bit pointless and silly.
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
//really dont understand what this is for... how have i recieved the message if it was sent to a different domain name... its like sending a letter to the wrong person and expecting the correct person to reply saying you sent it to someone else... but how does the right person even know you sent anything?
int hostnamecheck(char address[]){ // checks that the hostname matches gethostname()
	char hostname[BUFLEN];
	size_t size = strlen(hostname);
	gethostname(hostname, size);
	char local[] = "localhost";
	char dcssuf[] = ".dcs.gla.ac.uk";
    // not sure if i am meant to check against local the sheet was unclear to me regardless it was very helpful to have as ok whilst testing so it's here either way/
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
	else if(strcmp(ext, "css") == 0){//hope this isnt counted as over engineering, just the website i was testing on had css and i wanted to see what happened.
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

void cylcicalsend(char filename[], ssize_t connfd){
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

void response(char prot[], char filename[], char address[], ssize_t connfd){
	long size = 0;
	int res = 1;
	char sendstr[BUFLEN];
	char responsetype[SHORT] = "";
	char connection[SHORT] = "Connection: open\n";
	char length[SHORT] = "";
	char content[SHORT] = "text/html";
	char contentlong[BUFLEN] = "";
	char fourohfour[BUFLEN] = "<!doctype html><html>404\nNot Found</html>";
    char fourohoh[BUFLEN] = "<!doctype html><html>400\nBad Request</html>";
	char fiveohoh[BUFLEN] = "<!doctype html><html>500\nInternal Server Error</html>";
	sscanf(filename, "/%s", filename); //removes the slash from the file name
	res = responsecheck(filename, address);
	
	if (res == 0){
		strcpy(responsetype,"400 Bad Request\n");
        size = strlen(fourohoh);
	}
	else if (res == 1){
		strcpy(responsetype,"404 Not Found\n");
		size = strlen(fourohfour);
	}
	else if (res == 2){
		strcpy(responsetype,"200 OK\n");
		strcpy(content, contenttype(filename));
		size = filesize(filename);
    }
	else{
		strcpy(responsetype,"500 Internal Server Error\n");
		size = strlen(fiveohoh);
	}
    sprintf(contentlong, "Content-Type: %s\n", content);
    sprintf(length, "Content-Length: %ld\n", size);
    sprintf(sendstr, "%s %s%s%s%s\n",prot, responsetype, contentlong, connection, length);
    printf("%s", sendstr);
    write(connfd, sendstr, strlen(sendstr));
    if (res == 0){
		write(connfd,fourohoh, strlen(fourohoh));
	}
	else if (res == 1){
		write(connfd,fourohfour, strlen(fourohfour));
	}
    else if (res == 2){
        cylcicalsend(filename, connfd);
    }
	else{
		write(connfd,fiveohoh, strlen(fiveohoh));	
	}
    write(connfd, "\r\n", strlen("\r\n"));
}

void processrequest(int connfd){
	char method[BUFLEN] = "";
	char file[BUFLEN] = "";
	char host[BUFLEN] = "";
	char prot[BUFLEN] = "";
	char address[BUFLEN] = "";
	char* buf = malloc(BUFLEN);
	ssize_t rcount = 0;
	ssize_t rcounttotal = 0;
	int buflength = BUFLEN;
	while ((rcounttotal = read(connfd, buf, BUFLEN))>1){
		while (strstr(buf, "\r\n\r\n") == NULL){
			rcount = read(connfd, buf, buflength-rcounttotal);
			buflength = buflength * 2;
			buf = realloc(buf, buflength);
			rcounttotal += rcount;
		}
		getinputs(buf, method, file, prot, host);
		removeport(host, address);
		response(prot, file, address, connfd);
	}
}
	
void start_threads(thread_pool* threadpool){
    while(threadpool->connfd == -1){// i know that this is busy waiting, but i dont know enough about threads in C to do it using interupts or 		 		mutexs to make it work properly in a decent time frame
    }
	
	processrequest(threadpool->connfd);
	close(threadpool->connfd);
	threadpool->connfd = -1;
}

int main(void){
	extern int errno;
	struct sockaddr_in addr;
	struct sockaddr_in cliaddr;
	thread_pool* threadpool;
	ssize_t fd;
	int i;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	socklen_t cliaddrlen = sizeof(cliaddr);
	int set = 1;
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) ==-1){
		perror("Failed to fd socket");
	}
	
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(set));
	
	threadpool = malloc(sizeof(thread_pool)*THREADNUM);
	for (i = 0; i<THREADNUM; i++){
		(&threadpool[i])->thread = malloc(sizeof(pthread_t));
		initthreadpool(&threadpool[i]);
		
	}
	if((bind(fd, (struct sockaddr *)&addr, sizeof(addr))) == -1){
		perror("Port in use, failed to bind");
		return 0;
	}
	listen(fd, 1);
    for (i = 0; i<THREADNUM; i++){
        pthread_create((&threadpool[i])->thread, NULL,(void *)start_threads,(void *)&threadpool[i]);
    }
	while(1){
        
        for (i = 0; i<THREADNUM; i++){ // i know that this is busy waiting, but i dont know enough about threads in C to do it using interupts or 			mutexs to make it work properly in a decent time frame
			if ((&threadpool[i])->connfd == -1){;
				if(((&threadpool[i])->connfd = accept(fd, (struct sockaddr *) &cliaddr, &cliaddrlen)) ==-1){
					perror("Failed to accept request");				
				}
			}
        }
		
	}
	return 0;
    
}

