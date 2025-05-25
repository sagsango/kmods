MODULE := hello

obj-m := $(MODULE).o
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

run: all
	@echo "Inserting module..."
	@sudo insmod ./$(MODULE).ko || true
	@sleep 1
	@echo "dmesg output:"
	@sudo dmesg | tail -n 10
	@echo "Removing module..."
	@sudo rmmod $(MODULE) || true
	@sleep 1
	@echo "dmesg after removal:"
	@sudo dmesg | tail -n 10

