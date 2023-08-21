TARGET=diskam
CC=gcc
OBJS= \
	opcode.o\
	string.o\
	lex.yy.o\
	y.tab.o\
	common.o\
	compiler.o\
	create.o\
	../memory/mem.o\
	../debug/dbg.o\
	main.o\
	semantic.o\
	debug.o\
	codegen.o\
	../vm/vm.o \

CFLAGS = -c -g -Wall -Wswitch-enum -std=c11 -pedantic
INCLUDES = \
  -I/usr/local/include\
  -I../include

$(TARGET):$(OBJS)
	cd ../vm; $(MAKE);
	cd ../memory; $(MAKE);
	cd ../debug; $(MAKE);
	$(CC) $(OBJS) -o $@ -lm

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
../vm/vm.o:
	cd ../vm; $(MAKE);
############################################################
common.o: common.c ../include/MEM.h ../include/DBG.h decls.h
compiler.o: compiler.c ../include/MEM.h ../include/DBG.h decls.h
create.o: create.c ../include/MEM.h ../include/DBG.h decls.h
string.o: string.c ../include/MEM.h decls.h
semantic.o: semantic.c ../include/MEM.h decls.h
codegen.o: codegen.c ../include/MEM.h decls.h
opcode.o: opcode.c ../include/MEM.h decls.h
debug.o: debug.c ../include/MEM.h decls.h
main.o: main.c ../include/MEM.h
