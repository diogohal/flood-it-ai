CFLAGS = -std=c99 -Wall -g
all: floodit.o struct.o sma.o
	gcc $(CFLAGS) floodit.o struct.o sma.o -o floodit 

floodit.o: floodit.c
	gcc $(CFLAGS) -c floodit.c

struct.o: struct.c
	gcc $(CFLAGS) -c struct.c

sma.o: sma.c struct.c
	gcc $(CFLAGS) -c sma.c

clean:
	rm *.o *.temp

purge: clean
	rm -f floodit

run: all
	./floodit