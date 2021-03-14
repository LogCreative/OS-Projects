obj-m:=simple.o hello.o jiffies.o seconds.o
KDIR:=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm *.o *.ko *.mod.c Modules.symvers modules.order -f