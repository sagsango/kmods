# Kernel module
obj-m := mychar.o

# Kernel build setup
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

# Userspace program
USER_SRC := user_driver.c
USER_BIN := user_driver

all: $(USER_BIN) kmod

# Build userspace program
$(USER_BIN): $(USER_SRC)
	@echo " Compiling userspace driver..."
	$(CC) -o $@ $<

# Build kernel module
kmod:
	@echo " Building kernel module..."
	$(MAKE) -C $(KDIR) M=$(PWD)

# Run full test
run: all
	@echo " >>> Please run the test manually (automation doesn't work) <<< "
	@echo " Inserting kernel module..."
	@sudo dmesg -C
	@sudo insmod mychar.ko || true
	@sleep 1
	@echo " Getting major number from dmesg..."
	@sudo dmesg | grep "mychar: registered" | tail -n1 | grep -oP 'major \K\d+' > major.tmp
	@MAJOR=$$(cat major.tmp); echo $$MAJOR; sudo mknod -m 666 /dev/mydevice c $$MAJOR 0
	@echo " Running userspace driver..."
	@./$(USER_BIN) &> out
	@echo " Cleaning up..."
	@sudo rm -f /dev/mydevice
	@sudo rmmod mychar
	@rm -f major.tmp

clean:
	@echo " Cleaning build files..."
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f $(USER_BIN) major.tmp

