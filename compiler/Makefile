TARGET=diskam
CC=gcc
OBJS= \
	string.o\
	lex.yy.o\
	y.tab.o\
	common.o\
	compiler.o\
	create.o\
	../memory/mem.o\
	../debug/dbg.o\
	main.o\

CFLAGS = -c -g -Wall -Wswitch-enum -std=c11 -pedantic
INCLUDES = \
  -I/usr/local/include\
  -I../include

$(TARGET):$(OBJS)
	cd ../memory; $(MAKE);
	cd ../debug; $(MAKE);
	$(CC) $(OBJS) -o $@ -lm -ltable

clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h *~
y.tab.h : diksam.y
	bison --yacc -dv diksam.y
y.tab.c : diksam.y
	bison --yacc -dv diksam.y
lex.yy.c : diksam.l diksam.y y.tab.h
	flex diksam.l
y.tab.o: y.tab.c decls.h ../include/MEM.h
	$(CC) -c -g $*.c $(INCLUDES)
lex.yy.o: lex.yy.c decls.h ../include/MEM.h
	$(CC) -c -g $*.c $(INCLUDES)
.c.o:
	$(CC) $(CFLAGS) $*.c $(INCLUDES)
../memory/mem.o:
	cd ../memory; $(MAKE);
../debug/dbg.o:
	cd ../debug; $(MAKE);
############################################################
common.o: common.c ../include/MEM.h ../include/DBG.h decls.h
compiler.o: compiler.c ../include/MEM.h ../include/DBG.h decls.h
create.o: create.c ../include/MEM.h ../include/DBG.h decls.h
string.o: string.c ../include/MEM.h decls.h
main.o: main.c ../include/MEM.h