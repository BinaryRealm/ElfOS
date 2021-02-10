#include "vga.h"
#include "gdt.h"
#include "idt.h"
extern void int_test(void);
void kernel_main(void)
{
    //EVENTUALLY FIX CURSER
    vga_clear(BLACK);
    
    uint8_t *msg1 = (uint8_t*) "Hello, World!";
    vga_print(msg1, WHITE, BLACK);
    vga_newline();
    
    uint8_t *msg2 = (uint8_t*) "OS will now initialize new GDT.";
    vga_print(msg2, WHITE, BLACK);
    vga_newline();
    
    write_gdt();
    init_and_activate_gdt();
    
    
    uint8_t *msg3 = (uint8_t*) "GDT Loaded";
    vga_print(msg3, WHITE, BLACK);
    vga_newline();
    
    
    uint8_t *msg4 = (uint8_t*) "OS will now initialize new IDT.";
    vga_print(msg4, WHITE, BLACK);
    vga_newline();
    
    write_idt();
    init_and_activate_idt();
    
    uint8_t *msg5 = (uint8_t*) "IDT Loaded";
    vga_print(msg5, WHITE, BLACK);
    vga_newline();
    asm("int $0"); //software interrupts do work
    //.asm("int $9"); //software interrupts do work
    vga_newline();
    
}







