CFLAGS = -std=c99 -Wall -g
all: floodit.o struct.o
	gcc $(CFLAGS) floodit.o struct.o -o floodit 

floodit.o: floodit.c
	gcc $(CFLAGS) -c floodit.c

struct.o: struct.c
	gcc $(CFLAGS) -c struct.c

clean:
	rm *.o *.temp

purge: clean
	rm floodit

run:
	./floodit