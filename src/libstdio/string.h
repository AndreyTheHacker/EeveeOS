#include "stdio.h"

void kern_itoh(unsigned long n, char sign, char *outbuf);
int kern_strcpy(char *dst,const char *src);
int kern_strlen(const char* str);
void kern_strcat(void *dest,const void *src);
void *kern_memset(void *dst,char val, int n);
void kern_old_memcpy(char *source, char *dest, int nbytes);
void *kern_memcpy(void *dst, void const *src, int n);
