#ifndef _VGA_H
#define _VGA_H

static const size_t VGA_WIDTH  = 80;
static const size_t VGA_HEIGHT = 25;
static const size_t VGA_BUFFER = 0xB8000;
static size_t VGA_BUFFER_SIZE;

size_t    terminal_row;
size_t    terminal_column;
uint8_t   terminal_color;
uint16_t *terminal_buffer;

// Hardware text mode color constants.
enum vga_color
{
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
};

#define FILLCHAR '_'

void terminal_initialize();
void terminal_putchar(char c);
void terminal_writestring(const char* data);

#endif // _VGA_H
