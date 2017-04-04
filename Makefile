CFLAGS=-pthread
CC=gcc $(CFLAGS)

all: assign2
assign2: assign2.c
	$(CC) -o assign2 assign2.c
assign2.o: assign2.c 
	$(CC) -c assign2.c
clean:
	rm -f assign2 assign2.o
run: assign2
	./assign2