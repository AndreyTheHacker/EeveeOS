__asm__(".code16\n");
__asm__("jmpl $0x0000, $main\n");

void kern_putc(const int c) {
	__asm__ __volatile__("int $0x10"::"a"(0x0e00|c),"b"(0x0007));
	// "a"(0x0e00|c),"b"(0x0007)
	// |- a is ax register
	// |- 0x0e00 is ah (0x0e) and al(0x00) register (little-endian)
	// |- b is bx register
	// |- 0x0007 is bh (0x00) and bl(0x07) register (little-endian)

	// ==int 0x10==
	// ah is function
	// al is char to print
	// bh is video page
	// bl is color
}

void kern_printc(const char *c) {
	while(*c) {
		__asm__ __volatile__("int $0x10"::"a"(0x0e00|*c),"b"(0x0007));
	++c;
	}
}

void kern_movecursor(const int x, const int y){
	//__asm__ __volatile__("int $0x10"::"a"(0x0200),"d"(y|x));
	__asm__ __volatile__("int $0x10"::"a"(0x0200),"b"(0x0007),"d"(y|(x*80)));
}

void kern_clearscreen(){
	kern_movecursor(0,0);	
	__asm__ __volatile__("int $0x10"::"a"(0x0600),"b"(0x0007),"c"(0x0000),"d"(0x184f));
}

void main() {
	kern_clearscreen();
	//kern_movecursor(80/2,24/2);
	kern_printc("It's EeveeOS. Evoi!");
	while(1){
		/*
			Doing nothing, because if I call kern_putc('A') (without while(1){}),
			Output will be: A AA[smile]AAAAAAAAA
		*/
	}
}
