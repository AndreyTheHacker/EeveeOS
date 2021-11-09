unsigned char kern_inb(unsigned short port)
{
  unsigned char ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void kern_outb(unsigned short port, unsigned char data)
{
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

unsigned long kern_inl(unsigned long port)
{
  unsigned long ret;
  asm volatile("inl %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void kern_outl(unsigned short port, unsigned long data)
{
  asm volatile("outl %0, %1" : "=a"(data) : "d"(port));
}
