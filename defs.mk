PREFIX = i686-linux-gnu-
CFLAGS = -Wall -Wextra -std=gnu99 -c -ffreestanding -O2 -m32
LDFLAGS = -T src/link.ld -nostdlib --nmagic
LDFLAGS_NOSCRIPT = -nostdlib --nmagic

STDIO_LIB = src/libstdio/
STDIO_LIB_OBJS = $(STDIO_LIB)/ports.o $(STDIO_LIB)/stdio.o $(STDIO_LIB)/keyboard.o
