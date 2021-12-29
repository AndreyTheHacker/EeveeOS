#ifndef PIC_H
#define PIC_H

#include <stdint.h>

#define PIC1        0x20
#define PIC2        0xA0
#define PIC1_COMMAND    PIC1
#define PIC1_DATA   0x21
#define PIC2_COMMAND    PIC2
#define PIC2_DATA   0xA1
#define PIC_EOI     0x20

#define ICW1 0x11
#define ICW4 0x01

void pic_init();
void irq_ack(uint8_t irq);

#endif