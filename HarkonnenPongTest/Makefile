UNAME=$(shell uname)

CCFLAGS=-Wall -O3 -std=gnu99
CC=gcc

all: pri

pri: main.o pong.o ctest.h pongtests.o
	$(CC) $(LDFLAGS) main.o pong.o pongtests.o -o pong

remake: clean all

%.o: %.c ctest.h
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -f pong *.o
