#git make
obj-m := axo_read.o 

KDIR  := /lib/modules/$(shell uname -r)/build
PWD   := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm Module.symvers modules.order *.ko *.o *.mod.c
