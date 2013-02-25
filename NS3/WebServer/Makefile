CC=gcc
CFLAGS=-W -Wall 

web_server: WebServer.o
	$(CC) -o $@ $^ -lpthread

%.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm *.o;
