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

void main() {
	kern_cls();
	kern_printc("It's EeveeOS! Evoi-evo!\n");
	kern_printc("Keyboard drivers are built-in, not loading...\n");
	kern_printc("Trying to switch to VGA graphics mode\n");
	int countdown = 5;
	char gb[8];
	char gb_[8];
	while(countdown!=0) {
		kern_itoa(countdown, gb);
		kern_printc(gb);
		kern_printc(" ticks remaining...\n");
		countdown--;
		kern_memcpy(gb_, gb, 8);
		sleep(0x010000000);
	}
	kern_printc("Okay...");
	sleep(0x010000000);
	__asm__ __volatile__("int $0x10"::"a"(0x4F02),"b"(0x1180));
	while(1){
		
	}
}
