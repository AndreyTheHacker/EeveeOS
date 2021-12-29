#include "string.h"

void itoh(unsigned long n, char sign, char *outbuf)
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

unsigned int digit_count(int num)
{
  unsigned int count = 0;
  if(num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}

void itoa(int num, char *number)
{
  int dgcount = digit_count(num);
  int index = dgcount - 1;
  char x;
  if(num == 0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }else{
    while(num != 0){
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}


int strcpy(char *dst, const char *src) {
    int i = 0;
    while ((*dst++ = *src++) != 0)
        i++;
    return i;
}
/*
void kern_old_memcpy(char *source, char *dest, int nbytes) {
    for (int i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}
*/
void *memcpy(void *dst, void const *src, int n)
{
    char * ret = dst;
    char * p = dst;
    const char * q = src;
    while (n--)
        *p++ = *q++;
    return ret;
}
/*
int kern_old_strlen(const char* str) {
  unsigned int length = 0;
  while(str[length]==0){
	length++;
  }
  return length;
}
*/
int strlen(const char * s) {
    int len = 0;
    while(*s++)
        len++;
    return len;
}

void *memset(void *dst,char val, int n)
{
    char *temp = dst;
    for(;n != 0; n--) *temp++ = val;
    return dst;
}

void strcat(void *dest, const void *src) {
    char * end = (char*)dest + strlen(dest);
    memcpy((char*)end,(char*)src,strlen((char*)src));
    end = end + strlen((char*)src);
    //*end = '\0';
}
