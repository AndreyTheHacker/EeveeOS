#include "libstdio/stdio.h"
#include "libstdio/ports.h"
#include "libstdio/keyboard.h"
#include "libstdio/string.h"
#include "multiboot.h"
#include "memory/memmgr.h"
#include "memory/heap.h"
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
	memmgr_init(mb->mem_upper*1024);
	kheap_init(67108864/2,(67108864/2)+(48*1024),mb->mem_upper*1024); //32MB
	kern_printc("Memory manager initialized\n");	
	char *memlw = (char*)malloc(32);
	char mander; // IT's JOKE?
	char *memup = (char*)malloc(32);
	char *loadaddr = (char*)malloc(32);
	char *mgc = (char*)malloc(32);
	char flgs[32];
	char *memmessage = (char*)malloc(256);
	//kern_memset(memmessage, 0, 256);
	itoa(mb->mem_lower, memlw);
	itoa(mb->mem_upper, memup);
	itoh(magic, ' ', mgc);
	itoh(mb->flags, ' ', flgs);
	itoh(addr, ' ' ,loadaddr);
	if (CHECK_FLAG (mb->flags, 0)) {
    	strcpy(memmessage,"EeveeOS runs on ");
		strcat(memmessage,memlw);
    	strcat(memmessage,"KB of lower memory and ");
		strcat(memmessage,memup);
    	strcat(memmessage,"KB of upper memory\n");
    	kern_printc(memmessage);
		free(memmessage);
		free(memlw);
		free(memup);
		free(loadaddr);
    }else{
    	kern_printc("EeveeOS can't check memory (is 0x00000002 flag set?) :(\n");
    }
	kern_printc("Magic: ");
	kern_printc(mgc);
	free(mgc);
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
		itoa((second&0x0f)+(second/16)*10,seconds);
		itoa((minute&0x0f)+(minute/16)*10,minutes);
		itoa(((hour&0x0f)+((hour&0x70)/16)*10) | (hour & 0x80),hours);
	}else{
		itoa(second,seconds);
		itoa(minute,minutes);
		itoa(hour,hours);
	}
	strcpy(time,"Time: ");
	strcat(time,hours);
	strcat(time,":");
	strcat(time,minutes);
	strcat(time,":");
	strcat(time,seconds);
	strcat(time,"\n");
	kern_printc(time);
	char *meleon = (char*)malloc(16);
	meleon[0]='C';
	meleon[1]='H';
	meleon[2]='A';
	meleon[3]='R';
	meleon[4]='M';
	meleon[5]='E';
	meleon[6]='L';
	meleon[7]='E';
	meleon[8]='O';
	meleon[9]='N';
	kern_printc(meleon);
	free(meleon);
	while(1){
		kern_putc(kern_kbd_char(kern_getch()));
		wait_ticks(0x02D45A00);
	}
	//__asm__ __volatile__("int $0x10"::"a"(0x4F02),"b"(0x118));  // What a hell? GRUB disallows to enter graphical mode
	//__asm__ __volatile__("int $0x10"::"a"(0x0013));	// And this not working
	while(1){
		
	}
}
