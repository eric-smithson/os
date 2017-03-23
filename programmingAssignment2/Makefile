obj-m += assignment2Mod.o
BUILDDIR= build

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
