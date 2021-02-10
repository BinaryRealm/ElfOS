#include "vga.h"


//These functions are only called by wrappers in interrupt_wrappers.asm

void routine0(void)
{
    uint8_t *msg1 = (uint8_t*) "Routine at INT - activated";
    vga_print(msg1, WHITE, BLACK);
    //asm("mov $20h,%al");
    //asm("out %al, $20h");
}

void routine1(void)
{
    uint8_t *msg1 = (uint8_t*) "Routine at INT 51 activated";
    vga_print(msg1, WHITE, BLACK);
}

void routine2(void)
{
    
}
