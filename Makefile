all:
	mkdir build || true
	mkdir temps || true
	as --32 src/boot.asm -o temps/boot.o
	i686-linux-gnu-gcc -Wall -Wextra -std=gnu99 -c -ffreestanding -O2 -m32 src/main.c -o temps/main.o
	i686-linux-gnu-ld -T src/link.ld -nostdlib --nmagic temps/boot.o temps/main.o -o build/main.bin
	#setup
	mkdir build/boot/grub/ -p || true
	cp src/grub.cfg build/boot/grub/grub.cfg	
	grub-mkrescue build/ -o total.iso
	qemu-system-x86_64 -s -cdrom total.iso

clean:
	rm build/* -r || true
	rm temps/* -r || true
	rm total.iso || true
