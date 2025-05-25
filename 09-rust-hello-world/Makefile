# Module name (no .o or .ko)
MODULE := hello_world

# Object to build
obj-m := $(MODULE).o
$(MODULE)-objs := rust/lib.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

# Default target
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

# Clean target
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

