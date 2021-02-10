#include <stdint.h>
#define WIDTH 80
#define HEIGHT 25
#define AREA WIDTH * HEIGHT
#define VGA_BUFFER_START 0xb8000


enum vga_color{
    BLACK = 0,
    BLUE = 1,
    LIGHT_GREEN = 2,
    TURQUOISE = 3,
    RED = 4,
    MAGENTA = 5,
    LIGHT_ORANGE = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LAVENDER = 9,
    GREEN = 10,
    LIGHT_BLUE = 11,
    PINK_RED = 12,
    PINK = 13,
    YELLOW = 14,
    WHITE = 15
};


//to clear screen
uint16_t vga_b_color_format(uint8_t b_color);
void vga_clear(uint8_t b_color);

//to print letters
uint16_t vga_letter_format(uint8_t c, uint8_t t_color, uint8_t b_color);
void vga_grid_putchar(uint8_t c, uint8_t row, uint8_t column, uint8_t t_color, uint8_t b_color);
void vga_putchar(uint8_t c,uint8_t t_color, uint8_t b_color);
void vga_grid_print(uint8_t *s, uint8_t row, uint8_t column, uint8_t t_color, uint8_t b_color);
void vga_print(uint8_t *s,uint8_t t_color, uint8_t b_color);

//extra features
void vga_newline(void);
void vga_tab(void);
void print_int(uint32_t num);
void print_hexint(uint32_t num);
