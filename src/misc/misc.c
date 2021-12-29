#include "misc.h"

void _assert(char a) {
	_kern_printc("PANIC!!!",10,0); for(;;){}
}