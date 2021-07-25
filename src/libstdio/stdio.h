unsigned short kern_generate_vga(unsigned char c, unsigned short fc, unsigned short bc);
void _kern_putc(char c, unsigned short fc, unsigned short bc);
void kern_putc(char c);
int kern_strlen(const char* str);
void kern_printc(char *c);
void kern_cls();
void kern_vgashift(unsigned int val);
