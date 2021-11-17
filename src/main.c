#include "libstdio/stdio.h"
#include "libstdio/ports.h"
#include "libstdio/keyboard.h"
#include "libstdio/string.h"
#include "multiboot.h"
#include "memory/memmgr.h"
#include <stdint.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

void wait_ticks(unsigned int timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}

uint8_t read_rtc(int r){
	kern_outb(0x70,r);
	return kern_inb(0x71);
}

void main(unsigned long magic, unsigned long addr) { // GRUB
	kern_cls();
	multiboot_info_t *mb;
	mb = (multiboot_info_t *) addr;
	kern_printc("It's EeveeOS! Evoi-evo!\n");
	char memlw[32];
	char mander[1]; // IT's JOKE?
	char memup[32];
	char loadaddr[32];
	char mgc[32];
	char flgs[32];
	char memmessage[256];
	//kern_memset(memmessage, 0, 256);
	kern_itoa(mb->mem_lower, memlw);
	kern_itoa(mb->mem_upper, memup);
	kern_itoh(magic, ' ', mgc);
	kern_itoh(mb->flags, ' ', flgs);
	kern_itoh(addr, ' ' ,loadaddr);
	if (CHECK_FLAG (mb->flags, 0)) {
    	kern_strcpy(memmessage,"EeveeOS runs on ");
		kern_strcat(memmessage,memlw);
    	kern_strcat(memmessage,"KB of lower memory and ");
		kern_strcat(memmessage,memup);
    	kern_strcat(memmessage,"KB of upper memory\n");
    	kern_printc(memmessage);
    }else{
    	kern_printc("EeveeOS can't check memory (is 0x00000002 flag set?) :(\n");
    }
	kern_printc("Magic: ");
	kern_printc(mgc);
	kern_printc("\n");
	kern_printc("Flags: ");
	kern_printc(flgs);
	kern_printc("\n");
	kern_printc("Keyboard drivers are built-in, not loading...\n");
	kern_printc("Paging enabled in boot...\n");
	char time[64];
	char seconds[8];
	short second = read_rtc(0);
	char minutes[8];
	short minute = read_rtc(2);
	char hours[8];
	short hour = read_rtc(4);
	if(!(read_rtc(0x0b)&0x04)){
		kern_itoa((second&0x0f)+(second/16)*10,seconds);
		kern_itoa((minute&0x0f)+(minute/16)*10,minutes);
		kern_itoa(((hour&0x0f)+((hour&0x70)/16)*10) | (hour & 0x80),hours);
	}else{
		kern_itoa(second,seconds);
		kern_itoa(minute,minutes);
		kern_itoa(hour,hours);
	}
	kern_strcpy(time,"Time: ");
	kern_strcat(time,hours);
	kern_strcat(time,":");
	kern_strcat(time,minutes);
	kern_strcat(time,":");
	kern_strcat(time,seconds);
	kern_strcat(time,"\n");
	kern_printc(time);
	memmgr_init(mb->mem_upper*1024);
	kern_printc("Memory manager initialized");
	while(1){
		kern_putc(kern_kbd_char(kern_getch()));
		wait_ticks(0x02F45A90);
	}
	//__asm__ __volatile__("int $0x10"::"a"(0x4F02),"b"(0x118));  // What a hell? GRUB disallows to enter graphical mode
	//__asm__ __volatile__("int $0x10"::"a"(0x0013));	// And this not working
	while(1){
		
	}
}
