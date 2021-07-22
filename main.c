__asm__(".code16\n");
__asm__("jmpl $0x0000, $main\n");

#include <stdint.h>
#define VGA_TEXT 0xb8000

uint16_t* vga = (uint16_t*)VGA_TEXT;
int pos = 0;

void kern_putc(const int c, uint8_t fc, uint8_t bc) {
	//__asm__ __volatile__("int $0x10"::"a"(0x0e00|c),"b"(0x0007));
	uint16_t ax = 0;
	uint8_t ah = 0, al = 0;
	ah = bc;
	ah <<= 4;
	ah |= fc;
	ax=ah;
	ax<<=8;
	al=c;
	ax|=al;
	vga[pos]=ax;
	pos++;
}

void kern_printc(const char *c) {
	while(*c) {
		kern_putc(*c,0,15);
		//*(volatile uint8_t*)(VGA_TEXT)=*c++;
	}
}

void main() {
	//kern_movecursor(1,11);
	//kern_printc("It's EeveeOS! Evoi-evo!");
	kern_putc('a',15,0);
	kern_putc('a'+1,15,0);
	kern_putc('a'+2,15,0);
	while(1){
		/*
			Doing nothing, because if I call kern_putc('A') (without while(1){}),
			Output will be: A AA[smile]AAAAAAAAA
		*/
	}
}
