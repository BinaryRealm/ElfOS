#include "idt.h"

struct lidt_data init_lidt_data(uint16_t entries, struct idt_gate* base_address){
    struct lidt_data d;
    d.table_limit = entries*8-1;
    d.base_address = base_address;
    return d;
}

struct idt_gate write_idt_entry(uint32_t offset, uint16_t segment_selector, uint8_t reserved, uint8_t gate_type, uint8_t DPL, uint8_t P)
{
    struct idt_gate e;
    e.offset_low = offset;
    e.segment_selector = segment_selector;
    e.reserved = reserved;
    e.flags =  (P<<7) | (DPL<<5) | (gate_type);
    e.offset_high = (offset>>16);
    return e;
}

void write_idt(void)
{
    my_lidt_data = init_lidt_data(IDT_ENTRIES, idt);//lidt command will be pointed to my_lgdt_data
    for(int i = 0; i<IDT_ENTRIES; i++)
    {
        idt[i] = write_idt_entry(isr0,0x8,0,0b1110,0,1);
    }
    //idt[9] = write_idt_entry(isr0,0x8,0,0b1110,0,1);
    //idt[51] = write_idt_entry(isr1,0x8,0,0b1110,0,1);
}
