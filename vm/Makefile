TARGET = vm.o
CC=gcc
CFLAGS = -c -g -Wall -std=c11 -pedantic -DDEBUG -Wno-sequence-point -Wswitch-enum 
OBJS = execute.o \
	   native.o \

$(TARGET):$(OBJS)
	ld -r -o $@ $(OBJS)
clean:
	rm -f *.o
.c.o:
	$(CC) $(CFLAGS) -I../include $*.c

execute.o: execute.c decls.h
native.o: native.c decls.h
