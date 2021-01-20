CC=gcc
CFLAGS= -Wall
DFLAGS=
PROGS = setBits showBits

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@

clean:
	rm -f $(PROGS) *.o ~*
