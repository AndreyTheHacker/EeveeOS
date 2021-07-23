all:
	mkdir build || true
	dd if=/dev/zero of=total.img bs=512 count=2880
	nasm boot.asm -o build/boot.bin
	dd if=build/boot.bin of=total.img bs=512 conv=notrunc
	i686-linux-gnu-gcc -Wall -c -g -ffreestanding -O2 -march=i686 main.c -o main.o
	i686-linux-gnu-ld -static -Tlink.ld -nostdlib --nmagic -o main.elf main.o
	i686-linux-gnu-objcopy -O binary main.elf build/main.bin

	rm main.o main.elf
	dd if=build/main.bin of=total.img bs=512 seek=1 conv=notrunc
	qemu-system-x86_64 -s total.img

clean:
	rm build/*.bin || true
	rm total.img || true
