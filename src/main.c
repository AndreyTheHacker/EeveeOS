#include "libstdio/stdio.h"
#include "libstdio/ports.h"
#include "libstdio/keyboard.h"
#include "multiboot.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

void wait_for_io(unsigned int timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}

void kern_itoh(unsigned long n, char sign, char *outbuf)
{
    int i = 12; int j = 0;
    do{
        outbuf[i] = "0123456789ABCDEF"[n % 16];i--;n = n/16;
    }while( n > 0);
    if(sign != ' '){
        outbuf[0] = sign;++j;
    }
    while( ++i < 13){
       outbuf[j++] = outbuf[i];
    }
    outbuf[j] = 0;
}

void sleep(unsigned int timer_count)
{
  wait_for_io(timer_count);
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
	char mct[8];
	kern_itoa(mb->mem_lower, memlw);
	kern_itoa(mb->mem_upper, memup);
	kern_itoh(magic, ' ', mgc);
	kern_itoh(mb->flags, ' ', flgs);
	kern_itoh(addr, ' ' ,loadaddr);
	if (CHECK_FLAG (mb->flags, 0)) {
    	kern_printc("EeveeOS runs on ");
		kern_printc(memlw);
    	kern_printc("KB of lower memory and ");
		kern_printc(memup);
    	kern_printc("KB of upper memory\n");
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
	float mc = 1000;
	while (mc/7>0){
		kern_itoa(mc, mct);
		kern_printc(mct);
		kern_printc(" - 7 = ");
		mc-=7;
		mct[0] = 0;
		mct[1] = 0;
		mct[2] = 0;
		mct[3] = 0;
		kern_itoa(mc, mct);
		kern_printc(mct);
		kern_printc(" JUST FOR DEBUG");
		kern_printc("\n");
	}
	kern_printc("ZapeKin Petya krutoi chel.\n");
	kern_printc("    1000-7");
	//__asm__ __volatile__("int $0x10"::"a"(0x4F02),"b"(0x118));  // What a hell? GRUB disallows to enter graphical mode
	//__asm__ __volatile__("int $0x10"::"a"(0x0013));	// And this not working
	while(1){
		
	}
}
