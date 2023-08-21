TARGET = vm.o
CC=gcc
CFLAGS = -c -g -Wall -Wswitch-enum -std=c11 -pedantic -DDEBUG
OBJS = execute.o


$(TARGET):$(OBJS)
	ld -r -o $@ $(OBJS)
clean:
	rm -f *.o
.c.o:
	$(CC) $(CFLAGS) -I../include $*.c

execute.o: execute.c

