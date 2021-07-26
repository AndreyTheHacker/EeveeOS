#include "libstdio/stdio.h"
#include "libstdio/ports.h"
#include "libstdio/keyboard.h"

void wait_for_io(unsigned int timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}

void sleep(unsigned int timer_count)
{
  wait_for_io(timer_count);
}

void kern_input_routine(char *buf) {
	int kbd_pos = 0;
	char ch = 0;
	short keycode = 0;
	short shift = 0;
	do{
		keycode = kern_getch();
	    switch(keycode){
			case KEY_ENTER: {
				kern_putc('\n');
				buf[kbd_pos]='\0';
				goto exit_loop;
				break;
			}
			case KEY_BACKSPACE: {
				if(kbd_pos>0){
					kern_vgashift(-1);
					_kern_putc(' ',0,0);
					kern_vgashift(-1);
					kbd_pos--;
					buf[kbd_pos]=' ';
				}
				break;
			}
			case 0x2A:
			case 0x36:
				shift = 1;
				kern_vga_putat_xy('0'+shift,69,0);
				break;
			case 0xAA:
			case 0xB6:
				shift = 0;
				kern_vga_putat_xy('0'+shift,69,0);
				break;
		    default: {
		    	ch = kern_kbd_char(keycode);
				kern_putc(ch);
				char str_x[8];
				char str_y[8];
				kern_itoa(kern_vga_getpos_x(),str_x);
				kern_itoa(kern_vga_getpos_y(),str_y);
				kern_vga_putat_xy(str_x[0],70,0);
				kern_vga_putat_xy(str_x[1],71,0);
				kern_vga_putat_xy(str_x[2],72,0);
				kern_vga_putat_xy(str_y[0],74,0);
				kern_vga_putat_xy(str_y[1],75,0);
				kern_vga_putat_xy(str_y[2],76,0);
	    		buf[kbd_pos]=ch;
	    		kbd_pos++;
	    	}
		}
		sleep(0x02FFFF10);
	}while(ch > 0);
exit_loop:;
}

void main() {
	kern_cls();
	kern_printc("It's EeveeOS! Evoi-evo!\n");
	_kern_printc("Rhapsody (test string)\n",14,3);
	kern_printc("Trying to load keyboard drivers [built-in]\n");
	char bj[64];
	char empty[64];
	int w = 0;
	char w_[8];
	while(1){
		kern_itoa(w,w_);
		kern_printc(w_);
		kern_printc("\n");
		w++;
		sleep(0x02ffffff);
		//kern_printc("Type something > ");
		//kern_input_routine(bj);
		//kern_printc("You typed: ");
		//_kern_printc(bj,14,2);
		//kern_printc("\n");
		//kern_memcpy(empty,bj,64);
	}
}
