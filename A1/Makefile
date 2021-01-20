#makefile for assignment one

#gcc is the compiler
CC=gcc
#using -Wall for errors
CFLAGS=-Wall

#for gdb
DFLAGS=-g

#object files
OBJ=ass1.o

#header files, c file depends on this to compile
DEPS=ass1.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#making the binary
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o ~*
