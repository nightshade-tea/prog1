CFLAGS = -Wall -Wextra -g -std=c99
CC = gcc

all: tp2.o racional.o
	$(CC) -o tp2 tp2.o racional.o

racional.o: racional.c racional.h
	$(CC) -c $(CFLAGS) racional.c

tp2.o: tp2.c racional.h
	$(CC) -c $(CFLAGS) tp2.c

clean:
	rm -f *.o *~ tp2
