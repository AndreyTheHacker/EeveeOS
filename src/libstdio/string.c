#include "string.h"

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


int kern_strcpy(char *dst, const char *src) {
    int i = 0;
    while ((*dst++ = *src++) != 0)
        i++;
    return i;
}

void kern_old_memcpy(char *source, char *dest, int nbytes) {
    for (int i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void *kern_memcpy(void *dst, void const *src, int n)
{
    char * ret = dst;
    char * p = dst;
    const char * q = src;
    while (n--)
        *p++ = *q++;
    return ret;
}

int kern_old_strlen(const char* str) {
  unsigned int length = 0;
  while(str[length]==0){
	length++;
  }
  return length;
}

int kern_strlen(const char * s) {
    int len = 0;
    while(*s++)
        len++;
    return len;
}

void *kern_memset(void *dst,char val, int n)
{
    char *temp = dst;
    for(;n != 0; n--) *temp++ = val;
    return dst;
}

void kern_strcat(void *dest, const void *src) {
    char * end = (char*)dest + kern_strlen(dest);
    kern_memcpy((char*)end,(char*)src,kern_strlen((char*)src));
    end = end + kern_strlen((char*)src);
    //*end = '\0';
}
