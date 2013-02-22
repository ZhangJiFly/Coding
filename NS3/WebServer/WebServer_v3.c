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
#include <semaphore.h>
#define BUFLEN 8096
#define SHORT 30
	// CODE THAT MAY OR MAY NOT BE USED ONE DAY
	//char *timestr;
	//char temp[BUFLEN] = "";
	//sscanf(c_time_string,"%s %s %s %s %s \n",www,mmm,dd,time,yyyy);
	//sendstr = ("%s", www);
	//strcpy(temp,www);
	//strcat(strcat(strcat(temp, dd), mmm), yyyy); 
	//sendstr = strcat(temp, "\r\n");
	//sprintf(sendstr, "%s, %s %s %s \n", www, mmm, dd, yyyy);
	//printf("%s", sendstr);
	//sendstr = returnstring();
	//write(connfd, sendstr, strlen(sendstr));
	//free(connfd);
	//char www[4];
	//char dd[3];
	//char mmm[4];
	//char yyyy[4];
	//char time[4];
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

FILE* readcontent(char filename[],char filebuf[]){ // puts up to BUFLEN characters in a file into a buffer
	FILE *fd;

	sscanf(filename, "/%s", filename); //removes the slash from the file name

   	fd = fopen(filename, "r");

	if (fd != NULL){
			fread(filebuf, BUFLEN, 1, fd);
			fclose(fd);
	}
	
	return fd;
}


int responsecheck(char file[], char address[]){//determins what kind of response is sent e.g. 200 OK, 404 Not Fount etc.
	char filebuf[BUFLEN] = "";
	FILE *fd;
	int hostcheck;
	hostcheck = hostnamecheck(address);

	if (!hostcheck){
		return 0;
	}
	fd = readcontent(file, filebuf);
	printf("%s\n", file);	
	if (fd == NULL){
		return 1;
	}
	return 2;
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
void response(char prot[], char filename[], char address[], int connfd){
	long size;
	int res;
	char sendstr[BUFLEN];
	char responsetype[SHORT] = "";
	char connection[SHORT] = "Connection: open\n";
	char length[SHORT] = "";
	char filebuf[BUFLEN] ="";
	char content[SHORT] = "html/index";
	char contentlong[SHORT] = "";
	res = responsecheck(filename, address);
	size = filesize(filename);
	
    
    
	if (res == 0){
		strcpy(responsetype,"400 Bad Request\n");
		readcontent("400.html", filebuf);
		size = filesize("400.html");
	}
	if (res == 1){
		strcpy(responsetype,"404 Not Found\n");
		readcontent("404.html", filebuf);
		size = filesize("404.html");
	}
	if (res == 2){
		strcpy(responsetype,"200 OK\n");
		readcontent(filename, filebuf);
		contenttype(filename, content);
		size = filesize(filename);
	}
    
	sprintf(contentlong, "Content-Type: %s\n", content);
	sprintf(length, "Content-Length: %ld\n", size);
    
	sprintf(sendstr, "%s %s%s%s%s\n",prot, responsetype, contentlong, connection, length);
    
	printf("%s", sendstr);
    
	write(connfd, sendstr, strlen(sendstr));
	send(connfd, filebuf, sizeof(filebuf), 0);
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

int readport(){
	struct sockaddr_in addr;
	struct sockaddr_in cliaddr;
	int fd;
	int connfd;
	int valid;
	char buf[BUFLEN] = "";
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	socklen_t cliaddrlen = sizeof(cliaddr);
	int set = 1;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(set));
	if((valid = bind(fd, (struct sockaddr *)&addr, sizeof(addr))) == -1){
		perror("Port in use, failed to bind");
		//while (valid == -1){
			//(valid = bind(fd, (struct sockaddr *)&addr, sizeof(addr)));
		//}
		perror("Port now bound");
		return -1;
	}
	
	listen(fd, 1);

	while(1){
		connfd = accept(fd, (struct sockaddr *) &cliaddr, &cliaddrlen);
	
		while (read(connfd, buf, BUFLEN)>1){
			processrequest(buf, connfd);
		
		}
	}
	return connfd;
}





int main(void){
	extern int errno;

	int connfd;

	connfd = readport();
	close(connfd);
	
	return 0;
}
