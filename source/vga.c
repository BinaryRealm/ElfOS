#include "vga.h"


uint16_t * vga_pointer = (uint16_t*) VGA_BUFFER_START;

uint16_t vga_letter_format(uint8_t c, uint8_t t_color, uint8_t b_color)
{
    uint16_t letter = ((uint16_t) b_color<<12) | ((uint16_t) t_color<<8) | ((uint16_t) c);
    return letter;
}

uint16_t vga_b_color_format(uint8_t b_color)
{
    uint16_t letter = ((uint16_t) b_color<<12) | (uint16_t) 0;
    return letter;
}

void vga_newline(void)
{
    vga_pointer += WIDTH;
    vga_pointer -= (((uint32_t)vga_pointer-VGA_BUFFER_START)%WIDTH)/2;
    //The conversion to uint32 allows the address to be represented as a number
    //every individual address represents one byte, so the result of the calculation
    // is in bytes.  However, the vga_pointer does pointer arithmetic in multiples
    // of words, 1 word = 2 bytes, so 1 byte = 1/2 word and multiplying by this
    //converts it to words.
}
void vga_tab(void){
    vga_pointer += 5;
}
void print_int(uint32_t num)
{
    int digit_count = 0;
    int temp = num;
    while(temp!=0){
        temp/=10;
        digit_count++;
    }
    uint8_t digits[digit_count];
    int mod;
    for (int i = digit_count-1 ;i>=0;i--) {
        mod = num%10;
        digits[i] = mod;
        num/=10;
    }
    for(int i = 0; i< digit_count; i++ ){
        switch(digits[i])
        {
            case 0:
                vga_putchar('0',BLACK, WHITE);
                break;
            case 1:
                vga_putchar('1',BLACK, WHITE);
                break;
            case 2:
                vga_putchar('2',BLACK, WHITE);
                break;
            case 3:
                vga_putchar('3',BLACK, WHITE);
                break;
            case 4:
                vga_putchar('4',BLACK, WHITE);
                break;
            case 5:
                vga_putchar('5',BLACK, WHITE);
                break;
            case 6:
                vga_putchar('6',BLACK, WHITE);
                break;
            case 7:
                vga_putchar('7',BLACK, WHITE);
                break;
            case 8:
                vga_putchar('8',BLACK, WHITE);
                break;
            case 9:
                vga_putchar('9',BLACK, WHITE);
                break;
        }
    }
    
}
void print_hexint(uint32_t num)
{
    int digit_count = 0;
    int temp = num;
    while(temp!=0){
        temp/=16;
        digit_count++;
    }
    uint8_t digits[digit_count];
    int mod;
    for (int i = digit_count-1 ;i>=0;i--) {
        mod = num%16;
        digits[i] = mod;
        num/=16;
    }
    for(int i = 0; i< digit_count; i++ ){
        switch(digits[i])
        {
            case 0:
                vga_putchar('0',BLACK, WHITE);
                break;
            case 1:
                vga_putchar('1',BLACK, WHITE);
                break;
            case 2:
                vga_putchar('2',BLACK, WHITE);
                break;
            case 3:
                vga_putchar('3',BLACK, WHITE);
                break;
            case 4:
                vga_putchar('4',BLACK, WHITE);
                break;
            case 5:
                vga_putchar('5',BLACK, WHITE);
                break;
            case 6:
                vga_putchar('6',BLACK, WHITE);
                break;
            case 7:
                vga_putchar('7',BLACK, WHITE);
                break;
            case 8:
                vga_putchar('8',BLACK, WHITE);
                break;
            case 9:
                vga_putchar('9',BLACK, WHITE);
                break;
            case 10:
                vga_putchar('A',BLACK, WHITE);
                break;
            case 11:
                vga_putchar('B',BLACK, WHITE);
                break;
            case 12:
                vga_putchar('C',BLACK, WHITE);
                break;
            case 13:
                vga_putchar('D',BLACK, WHITE);
                break;
            case 14:
                vga_putchar('E',BLACK, WHITE);
                break;
            case 15:
                vga_putchar('F',BLACK, WHITE);
                break;
        }
    }
    
}

void vga_grid_putchar(uint8_t c, uint8_t row, uint8_t column, uint8_t t_color, uint8_t b_color){
    //max (24,79)
    uint16_t grid_location = 2*(row*WIDTH+column);
    vga_pointer = (uint16_t*) (VGA_BUFFER_START + grid_location);
    *vga_pointer = vga_letter_format(c, t_color, b_color);
    vga_pointer++;
}

void vga_putchar(uint8_t c,uint8_t t_color, uint8_t b_color)
{
    *vga_pointer = vga_letter_format(c, t_color, b_color);
    vga_pointer++;
}

void vga_grid_print(uint8_t *s, uint8_t row, uint8_t column, uint8_t t_color, uint8_t b_color)
{
    uint16_t grid_location = 2*(row*WIDTH+column);
    vga_pointer = (uint16_t*) (VGA_BUFFER_START + grid_location);
    int i = 0;
    while(s[i]!='\0')
    {
        *vga_pointer = vga_letter_format(s[i], t_color, b_color);
        vga_pointer++;
        i++;
    }
}

void vga_print(uint8_t *s,uint8_t t_color, uint8_t b_color)
{
    int i = 0;
    while(s[i]!='\0')
    {
        *vga_pointer = vga_letter_format(s[i], t_color, b_color);
        vga_pointer++;
        i++;
    }
}

void vga_clear(uint8_t b_color)
{
    for(int i = 0;i<(AREA); i++)
    {
        *vga_pointer = vga_b_color_format(b_color);
        vga_pointer++;
    }
    vga_pointer = (uint16_t*) VGA_BUFFER_START;
}
