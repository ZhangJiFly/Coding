CC= gcc
CFLAGS= -W -Wall

SOURCES=$(wildcard *.c)
EXECUTABLES=$(SOURCES:%.c=%)

all: $(EXECUTABLES)

%.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm *.o;
