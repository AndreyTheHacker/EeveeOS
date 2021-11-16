include ../../defs.mk

all:
	nasm -felf32 gdt_.asm	-o gdt_.o
	nasm -felf32 idt_.asm	-o idt_.o
	$(PREFIX)gcc $(CFLAGS) gdt.c -c -o gdt.o
	$(PREFIX)ld gdt_.o idt_.o -o desctab.o
