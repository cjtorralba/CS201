CC=gcc
CFLAGS= -Wall -lm
DFLAGS=
PROGS = main 

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@

clean:
	rm -f $(PROGS) *.o ~*
