# makefile for Producer-Consumer Problem
#

CC=gcc
CFLAGS=-Wall
PTHREADS=-lpthread

all: pcp.o buffer.o
	$(CC) $(CFLAGS) -o pcp pcp.o buffer.o $(PTHREADS)

pcp.o: pcp.c
	$(CC) $(CFLAGS) -c pcp.c $(PTHREADS)

buffer.o: buffer.c buffer.h
	$(CC) $(CFLAGS) -c buffer.c $(PTHREADS)

clean:
	rm -rf *.o
	rm -rf pcp

