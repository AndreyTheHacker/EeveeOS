include defs.mk

all:
	mkdir build || true
	mkdir temps || true
	cd $(STDIO_LIB) && make 
	as --32 src/boot.s -o temps/boot.o
	$(PREFIX)gcc $(CFLAGS) src/main.c -o temps/main.o
	$(PREFIX)ld $(LDFLAGS) temps/boot.o $(STDIO_LIB_OBJS) temps/main.o -o build/main.bin
	#setup
	mkdir build/boot/grub/ -p || true
	cp src/grub.cfg build/boot/grub/grub.cfg	
	grub-mkrescue build/ -o total.iso
	qemu-system-x86_64 -m 32M -s -cdrom total.iso

clean:
	rm build/* -r || true
	rm temps/* -r || true
	rm $(STDIO_LIB)/*.o -r || true
	rm total.iso || true
