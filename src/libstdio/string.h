#include "stdio.h"

void itoh(unsigned long n, char sign, char *outbuf);
int strcpy(char *dst,const char *src);
int strlen(const char* str);
void strcat(void *dest,const void *src);
void *memset(void *dst,char val, int n);
void *memcpy(void *dst, void const *src, int n);
unsigned int kern_digit_count(int num);
void kern_itoa(int num, char *number);