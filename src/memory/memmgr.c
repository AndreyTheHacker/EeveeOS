#include "memmgr.h"
#include "../libstdio/string.h"

uint8_t * bitmap = (uint8_t*)(&kend);
uint8_t * mem_start;
uint32_t total_blocks;
uint32_t bitmap_size;

void pmm_init(uint32_t mem_size) {
    total_blocks = mem_size / BLOCK_SIZE;
    bitmap_size = total_blocks / BLOCKS_PER_BUCKET;
    if(bitmap_size * BLOCKS_PER_BUCKET < total_blocks)
        bitmap_size++;

    kern_memset(bitmap, 0, bitmap_size);
    mem_start = (uint8_t*)BLOCK_ALIGN(((uint32_t)(bitmap + bitmap_size)));
    //kern_printc("mem size:     %u mb\n", mem_size / (1024 * 1024));
    //kern_printc("total_blocks: %u\n", total_blocks);
    //kern_printc("bitmap addr:  0x%p\n", bitmap);
    //kern_printc("bitmap_size:  %u\n", bitmap_size);
    //kern_printc("mem_start:    0x%p\n", mem_start);
}

/*
 * Find the first free block and return memory address of the block, also set corresponding bit in bitmap
 * */

uint32_t allocate_block() {
    uint32_t free_block = first_free_block();
    SETBIT(free_block);
    return free_block;
}

void free_block(uint32_t blk_num) {
    CLEARBIT(blk_num);
}

/*
 * Helper function for allocate_block(), return the first free block
 * */
uint32_t first_free_block() {
    uint32_t i;
    for(i = 0; i < total_blocks; i++) {
        if(!ISSET(i))
            return i;
    }
    return (uint32_t) -1;
}
