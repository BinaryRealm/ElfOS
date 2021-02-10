#include <stdint.h>
#define GDT_ENTRIES 3
struct __attribute__((packed)) gdt_entry
{
    uint16_t segment_limit_low;
    uint16_t base_address_low;
    uint8_t base_address_med;
    uint8_t flags;
    uint8_t flags2;
    uint8_t base_address_high;
};

struct __attribute__((packed)) lgdt_data
{
    uint16_t table_limit;//in bytes-1
    struct gdt_entry* base_address;
};

//global variables
struct lgdt_data my_lgdt_data;
__attribute__((aligned(8))) struct gdt_entry gdt[GDT_ENTRIES];//this is the gdt table

//struct initializers
struct lgdt_data init_lgdt_data(uint16_t entries, struct gdt_entry *base_address);
struct gdt_entry write_gdt_entry(uint32_t segment_limit, uint32_t base_address, uint8_t type, uint8_t S, uint8_t DPL, uint8_t P, uint8_t DB, uint8_t G);

//to be called in kernel_main
void write_gdt(void);
extern void init_and_activate_gdt(void);

