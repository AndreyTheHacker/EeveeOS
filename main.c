__asm__(".code16\n");
__asm__("jmpl $0x0000, $main\n");

#define VGA_TEXT 0xb8000

unsigned short* vga = (unsigned short*)VGA_TEXT;
unsigned int pos = 0;

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

void kern_putc(char c) {
	vga[pos]=kern_generate_vga(c,14,0);
	pos++;
}

int kern_strlen(const char* str)
{
  unsigned int length = 0;
  //kern_putc('0');
  while(str[length]!=0){
	length++;
  }
  return length;
}

void kern_printc(char *c) {
	kern_putc('0'+4);
	//unsigned int brt = kern_strlen("RAMMER");
	//kern_putc('0'); // should show 6 with yellow color
}

void main() {
	//kern_movecursor(1,11);
	//kern_putc('H',15,0);
	//kern_printc("It's EeveeOS! Evoi-evo!");
	kern_printc("POKEMON_"); // 8 char's
	while(1){
		/*
			Doing nothing, because if I call kern_putc('A') (without while(1){}),
			Output will be: A AA[smile]AAAAAAAAA
		*/
	}
}
