#define VGA_TEXT 0xb8000
#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e
#define NULL 0
//unsigned short kern_generate_vga(unsigned char c, unsigned short fc, unsigned short bc);
void _kern_putc(char c, unsigned short fc, unsigned short bc);
void kern_vga_putat(unsigned char c, int offset);
void _kern_vga_putat(unsigned char c, int offset, unsigned short fc, unsigned short bc);
void kern_vga_putat_xy(unsigned char c, unsigned int x, unsigned int y);
void _kern_vga_putat_xy(unsigned char c, unsigned int x, unsigned int y, unsigned short fc, unsigned short bc);
void kern_putc(char c);
void kern_printc(char *c);
void kern_cls();
void kern_vgashift(unsigned int val);

unsigned int kern_vga_getpos();
unsigned int kern_vga_getpos_x();
unsigned int kern_vga_getpos_y();
int kern_vga_getpos_char(int x, int y);
void _kern_printc(char *c, unsigned short fc, unsigned short bc);
int kern_scroll_ln(int offset);
