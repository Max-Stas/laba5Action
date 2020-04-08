CC=gcc
CFLAGS= -pedantic -std=c89

.PHONY: build run clean

all: build

build: a.out

a.out:
	$(CC) $(CFLAGS) task1.c

run: a.out
	./a.out

clean:
	rm -rf *.o *.txt a.out