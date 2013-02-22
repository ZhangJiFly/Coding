CC=gcc
CFLAGS=-W -Wall -Werror 

web_server: WebServer.o
	$(CC) -o $@ $^ -lpthread

%.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm *.o;
