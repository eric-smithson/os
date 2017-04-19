obj-m += assignment3write.o
obj-m += assignment3read.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	$(CC) test.c -o test
	$(CC) test_read.c -o test_read
	$(CC) test_write.c -o test_write
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm test
	rm test_read
	rm test_write
