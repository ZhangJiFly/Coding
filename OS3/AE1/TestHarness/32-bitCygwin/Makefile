CFLAGS=-W -Wall -pedantic
OBJECTS=BoundedBuffer.o diagnostics.o fakeapplications.o \
        freepacketdescriptorstore.o generic_queue.o \
        networkdevice.o networkdriver.o packetdescriptor.o \
        packetdescriptorcreator.o testharness.o

demo.exe: $(OBJECTS)
	cc -o demo.exe $(OBJECTS)

clean:
	rm -f *.o demo.exe
