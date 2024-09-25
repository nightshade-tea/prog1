CFLAGS = -Wall -Wextra -g -std=c99
CC = gcc

all: tp1.o racional.o
	$(CC) -o tp1 tp1.o racional.o

racional.o: racional.c racional.h
	$(CC) -c $(CFLAGS) racional.c

tp1.o: tp1.c racional.h
	$(CC) -c $(CFLAGS) tp1.c

clean:
	rm -f *.o *~ tp1
