#include <stdint.h>
#define IDT_ENTRIES 256
struct __attribute__((packed)) idt_gate
{
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t reserved;
    uint8_t flags;
    uint16_t offset_high;
};

struct __attribute__((packed)) lidt_data
{
    uint16_t table_limit;//in bytes-1
    struct idt_gate* base_address;
};

//global variables
struct lidt_data my_lidt_data;
__attribute__((aligned(8))) struct idt_gate idt[IDT_ENTRIES];//this is the idt table


//interrupt handler pointers
extern uint32_t isr0;
extern uint32_t isr1;
extern uint32_t isr2;

//struct initializers
struct lidt_data init_lidt_data(uint16_t entries, struct idt_gate* base_address);
struct idt_gate write_idt_entry(uint32_t offset, uint16_t segment_selector, uint8_t reserved, uint8_t gate_type, uint8_t DPL, uint8_t P);

//to be called in kernel_main
void write_idt(void);
extern void init_and_activate_idt(void);
