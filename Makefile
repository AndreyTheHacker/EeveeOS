all:
	dd if=/dev/zero of=total.img bs=512 count=2880
	nasm boot.asm -o out/boot.bin
	dd if=out/boot.bin of=total.img bs=512 conv=notrunc
	i686-linux-gnu-gcc -Wall -c -g -ffreestanding -O2 -march=i686 main.c -o main.o
	i686-linux-gnu-ld -static -Tlink.ld -nostdlib --nmagic -o main.elf main.o
	i686-linux-gnu-objcopy -O binary main.elf out/main.bin
	rm main.o main.elf
	dd if=out/main.bin of=total.img bs=512 seek=1 conv=notrunc
	qemu-system-x86_64 -s total.img
