#ifndef MISC_H
#define MISC_H
#include "../libstdio/stdio.h"

#define ASSERT(b) ((b) ? (void)0 : _assert(b))
#define abs(a) (((a) < 0)?-(a):(a))
#define max(a,b) (((a) > (b)) ? (a) : (b))

void _assert(char a);

#endif