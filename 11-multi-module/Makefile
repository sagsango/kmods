obj-m := mod_a.o mod_b.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD)

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

run: all
	@echo " Inserting mod_a..."
	@sudo insmod ./mod_a.ko || true
	@sleep 1
	@echo " Inserting mod_b (depends on mod_a)..."
	@sudo insmod ./mod_b.ko || true
	@sleep 1
	@echo " dmesg:"
	@sudo mesg | tail -n 15
	@echo " Removing mod_b..."
	@sudo rmmod mod_b || true
	@sleep 1
	@echo " Removing mod_a..."
	@sudo rmmod mod_a || true
	@sleep 1
	@echo " dmesg after removal:"
	@sudo dmesg | tail -n 15

