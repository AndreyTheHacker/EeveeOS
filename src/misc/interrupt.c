#include "isr.h"
#include "../libstdio/stdio.h"
#include "pic.h"

isr_t interrupt_handlers[256];

void register_interrupt_handler(int num, isr_t handler) {
    if(num < 256) interrupt_handlers[num] = handler;
}

void final_irq_handler(register_t * reg) {
    if(interrupt_handlers[reg->int_no] != NULL) {
        isr_t handler = interrupt_handlers[reg->int_no];
        handler(reg);
    }
    irq_ack(reg->int_no);
}
