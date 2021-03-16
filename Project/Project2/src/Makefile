obj-m:=pid.o
KDIR:=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

all:
	gcc -g osh.c -o osh
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm *.o *.ko *.mod.c Modules.symvers modules.order -f