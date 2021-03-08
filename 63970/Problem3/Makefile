obj-m += p3a.o
obj-m += p3b.o

all: parta partb

parta: p3a.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

partb: p3b.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
