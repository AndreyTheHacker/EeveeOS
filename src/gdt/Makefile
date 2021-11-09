include ../../defs.mk

all:
	nasm -felf32 gdt_helper.asm	-o build/gdt_helper.o
	$(PREFIX)gcc $(CFLAGS) gdt.c build/gdt_helper.o -c -o build/gdt.o
