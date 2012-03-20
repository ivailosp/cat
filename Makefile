CC=gcc
CFLAGS=-Wall
all:
	$(CC) $(CFLAGS) cat.c -o cat
clean:
	rm -rf *.o cat
