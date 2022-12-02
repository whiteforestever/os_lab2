obj-m += kernelm.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test: all
	sudo dmesg -C
	sudo insmod kernelm.ko
	sudo rmmod kernelm.ko
	dmesg