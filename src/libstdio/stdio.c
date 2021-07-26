#include "stdio.h"
#include "ports.h"

unsigned char* vga = (unsigned char*)VGA_TEXT;
unsigned int vga_pos = 0;

void kern_vgashift(unsigned int val) {
	vga_pos+=val+1;
}

void _kern_vga_putat_xy(unsigned char c, unsigned int x, unsigned int y, unsigned short fc, unsigned short bc) {
	//y*=2;
	//x*=2;
	unsigned short ax = 0;
	unsigned char ah = 0/*, al = 0*/;
	ah = bc;
	ah <<= 4;
	ah |= fc;
	ax=ah;
	ax<<=8;
	//al=c;
	//ax|=al;
	vga[(y*80)+x]=c;
	vga[(y*80)+x+1]=ax;
}

void kern_vga_putat_xy(unsigned char c, unsigned int x, unsigned int y) {
	_kern_vga_putat_xy(c,x,y,14,0);
}

void _kern_vga_putat(unsigned char c, int offset, unsigned short fc, unsigned short bc) {
	offset*=2;
	unsigned short ax = 0;
	unsigned char ah = 0/*, al = 0*/;
	ah = bc;
	ah <<= 4;
	ah |= fc;
	ax=ah;
	ax<<=8;
	//al=c;
	//ax|=al;
	vga[offset]=c;
	vga[offset+1]=ax;
}

void kern_vga_putat(unsigned char c, int offset) {
	_kern_vga_putat(c,offset,14,0);
}

void kern_memcpy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void kern_set_cursor(int offset) {
    offset /= 2;
    kern_outb(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    kern_outb(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
    kern_outb(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    kern_outb(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

int kern_get_cursor() {
    kern_outb(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    int offset = kern_inb(VGA_DATA_REGISTER) << 8;
    kern_outb(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset += kern_inb(VGA_DATA_REGISTER);
    return offset*2;
}
/*
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
*/
void _kern_putc(char c, unsigned short fc, unsigned short bc) {
	if(vga_pos>=80*25*2) {
		vga_pos=kern_scroll_ln(vga_pos);
	}
	if(c!='\n'){
		unsigned short ax = 0;
		unsigned char ah = 0/*, al = 0*/;
		ah = bc;
		ah <<= 4;
		ah |= fc;
		ax=ah;
		ax<<=8;
		//al=c;
		//ax|=al;
		vga[vga_pos]=c;
		vga[vga_pos+1]=ah;
		//vga[vga_pos]=kern_generate_vga(c,fc,bc);
		vga_pos+=2;
	}else{
		vga_pos=vga_pos+(160-(vga_pos%160));
	}
	//kern_set_cursor(kern_get_cursor());
}

void kern_putc(char c) {
	if(vga_pos>=80*25*2) {
		vga_pos=kern_scroll_ln(vga_pos);
	}
	if(c!='\n'){
		_kern_putc(c,14,0);
	}else{
		vga_pos=vga_pos+(160-(vga_pos%160));
	}
	kern_set_cursor(kern_get_cursor());
}

int kern_strlen(const char* str)
{
  unsigned int length = 0;
  while(str[length]==0){
	length++;
  }
  return length;
}

int kern_scroll_ln(int offset) {
    kern_memcpy(
            (char *)(kern_vga_getpos_char(0,1) + VGA_TEXT), // source [vga:80]
            (char *)(kern_vga_getpos_char(0,0) + VGA_TEXT), // destin [vga:0]
           80*24*2 // 1920
    );
    for (int col = 0; col < 80; col++) {
       _kern_vga_putat(' ', kern_vga_getpos_char(col, 24),0,0);
    }
    return offset-160;
}

void _kern_printc(char *c, unsigned short fc, unsigned short bc) {
	while(*c!=0){
		_kern_putc(*c,fc,bc);
		c++;
	}
}

void kern_printc(char *c) {
	while(*c!=0){
		kern_putc(*c);
		c++;
	}
}

unsigned int kern_vga_getpos() {
	return 2*vga_pos;
}

unsigned int kern_vga_getpos_x() {
	return 2*vga_pos%80;
}

unsigned int kern_vga_getpos_y() {
	return 2*(int)(vga_pos/80);
}

int kern_vga_getpos_char(int x, int y) {
	return 2*(y*80+x);
}

void kern_cls(){
	for(unsigned int i=0; i<80*25*2;i++){
		_kern_putc(' ',0,0);
	}
	vga_pos=0;
}

unsigned int kern_digit_count(int num)
{
  unsigned int count = 0;
  if(num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}

void kern_itoa(int num, char *number)
{
  int dgcount = kern_digit_count(num);
  int index = dgcount - 1;
  char x;
  if(num == 0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }else{
    while(num != 0){
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}
