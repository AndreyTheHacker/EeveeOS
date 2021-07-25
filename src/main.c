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

void kern_input_routine() {
	int kbd_pos = 0;
	char ch = 0;
	char keycode = 0;
	int shift = 0;
	do{
		keycode = kern_getch();
	    switch(keycode){
			case KEY_ENTER: {
				kern_putc('\n');
				kbd_pos=0;
				break;
			}
			case KEY_BACKSPACE: {
				if(kbd_pos>0){
					kern_vgashift(-1);
					_kern_putc(' ',0,0);
					kern_vgashift(-1);
					kbd_pos--;
				}
				break;
			}
			case 0x2A:
			case 0x36:
				break;
		    default: {
		    	ch = kern_kbd_char(keycode);
	    		kern_putc(ch);
	    		kbd_pos++;
	    	}
		}
		sleep(0x02FFFF90);
	}while(ch > 0);
}

void main() {
	kern_cls();
	kern_printc("It's EeveeOS! Evoi-evo!\n");
	kern_printc("Trying to load keyboard drivers [built-in]\n");
	while(1){
		kern_input_routine();
	}
}
