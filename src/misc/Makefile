include ../../defs.mk

all:
	as --32 spinlock.asm -o spinlock.o
	$(PREFIX)gcc $(CFLAGS) misc.c -o misc.o
	$(PREFIX)gcc $(CFLAGS) isr.c -o isr.o
	$(PREFIX)gcc $(CFLAGS) interrupt.c -o interrupt.o
	$(PREFIX)gcc $(CFLAGS) pic.c -o pic.o