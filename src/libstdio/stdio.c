#include "stdio.h"
#include "ports.h"
#define VGA_TEXT 0xb8000

unsigned short* vga = (unsigned short*)VGA_TEXT;
unsigned int vga_pos = 0;

void kern_vgashift(unsigned int val) {
	vga_pos+=val;
}

unsigned short kern_generate_vga(unsigned char c, unsigned short fc, unsigned short bc) {
	unsigned short ax = 0;
	unsigned char ah = 0, al = 0;
	ah = bc;
	ah <<= 4;
	ah |= fc;
	ax=ah;
	ax<<=8;
	al=c;
	ax|=al;
	return ax;
}

void _kern_putc(char c, unsigned short fc, unsigned short bc) {
	vga[vga_pos]=kern_generate_vga(c,fc,bc);
	vga_pos++;
}

void kern_putc(char c) {
	if(c!='\n'){
	_kern_putc(c,14,0);
	}else{
		vga_pos=vga_pos+(80-(vga_pos%80));
	}
}

int kern_strlen(const char* str)
{
  unsigned int length = 0;
  while(str[length]==0){
	length++;
  }
  return length;
}

void kern_printc(char *c) {
	while(*c){
		kern_putc(*c);
		c++;
	}
}

void kern_cls(){
	for(unsigned int i=0; i<80*25;i++){
		_kern_putc(' ',0,0);
	}
	vga_pos=0;
}
