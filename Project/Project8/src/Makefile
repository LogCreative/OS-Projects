CC=gcc
CFLAGS=-Wall

all: addext.o memory.o pagetab.o lru.o tlb.o vmm.o 
	$(CC) $(CFLAGS) -o vmm addext.o memory.o pagetab.o lru.o tlb.o vmm.o

addext.o: addext.c
	$(CC) $(CFLAGS) -c addext.c

vmm.o: vmm.c
	$(CC) $(CFLAGS) -c vmm.c

memory.o: memory.c
	$(CC) $(CFLAGS) -c memory.c

pagetab.o: pagetab.c
	$(CC) $(CFLAGS) -c pagetab.c

lru.o: lru.c
	$(CC) $(CFLAGS) -c lru.c

tlb.o: tlb.c
	$(CC) $(CFLAGS) -c tlb.c

clean:
	rm -rf *.o
	rm -rf vmm