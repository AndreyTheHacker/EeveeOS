PREFIX = i686-linux-gnu-
CFLAGS = -Wall -Wextra -std=gnu99 -c -ffreestanding -O2 -m32
LDFLAGS = -T src/link.ld -nostdlib --nmagic
LDFLAGS_NOSCRIPT = -nostdlib --nmagic

STDIO_LIB = src/libstdio/
STDIO_LIB_OBJS = $(STDIO_LIB)/ports.o $(STDIO_LIB)/string.o $(STDIO_LIB)/stdio.o $(STDIO_LIB)/keyboard.o

GDT_LIB = src/gdt/
GDT_LIB_OBJS = $(GDT_LIB)/desctab.o

MEMORY = src/memory/
MEM_OBJS = $(MEMORY)/memmgr.o $(MEMORY)/heap.o $(MEMORY)/paging_wrk.o

MISC = src/misc/
MISC_OBJS = $(MISC)/spinlock.o $(MISC)/misc.o $(MISC)/isr.o $(MISC)/interrupt.o $(MISC)/pic.o
