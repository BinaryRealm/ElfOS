#include "gdt.h"

struct lgdt_data init_lgdt_data(uint16_t entries, struct gdt_entry *base_address)
{
    struct lgdt_data d;
    d.table_limit = entries*8-1;
    d.base_address = base_address;
    return d;
}

struct gdt_entry write_gdt_entry(uint32_t segment_limit, uint32_t base_address, uint8_t type, uint8_t S, uint8_t DPL, uint8_t P, uint8_t DB, uint8_t G)
{
    struct gdt_entry e;
    e.segment_limit_low = segment_limit;  //uint16_t segment_limit_low;
    e.base_address_low =  base_address;     //uint16_t base_address_low;
    e.base_address_med =  (base_address&0x00FF0000)>>16;    //uint8_t base_address_med;
    e.flags =             (P<<7)|(DPL<<5)|(S<<4)|(type);         //uint8_t flags;
    e.flags2 =            (G<<7)|(DB<<6)|(0<<5)/*64bitmode*/|(0<<4)/*AVL*/|((segment_limit&0x000F0000)>>16);
    //uint8_t flags2;
    e.base_address_high = base_address>>24;    //uint8_t base_address_high;*/
    return e;
}

void write_gdt(void)
{
    /*In this case, the code and data segments overlap the full possible address space of
     memory(4GB) from address 0.  Even though I set the code segment to be "read only", the
     data segments overlap it anyways, so it is all readable and writable in practice.
     It is essentially a real mode that is 32 bit.  So until paging is activated and
     user space settings are created, this is all a kernel land. */
    
    my_lgdt_data = init_lgdt_data(GDT_ENTRIES, gdt); //lgdt command will be pointed to my_lgdt_data
    gdt[0] = write_gdt_entry(0,0,0,0,0,0,0,0);
    gdt[1] = write_gdt_entry(0xFFFFF,0,10,1,0,1,1,1);  //code segment
    gdt[2] = write_gdt_entry(0xFFFFF,0,2,1,0,1,1,1);    //the rest (data segments)
}


