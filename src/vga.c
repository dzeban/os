#include <stddef.h>
#include <stdint.h>

#include "vga.h"
#include "lib.h"

static uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static uint16_t make_vgaentry(char c, uint8_t color)
{
    uint16_t char16 = c;
    uint16_t color16 = color;
    return char16 | color16 << 8;
}

static void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

/* Updates the hardware cursor: the little blinking line
 * on the screen under the last character pressed! */
void move_csr(void)
{
    uint16_t temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = terminal_row * 80 + terminal_column;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}
static void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(c, color);
}

static void terminal_scroll()
{
    uint16_t *dst = terminal_buffer;
    uint16_t *src = terminal_buffer + VGA_WIDTH;
    int len = VGA_BUFFER_SIZE - VGA_WIDTH;

    while(len--)
        *dst++ = *src++;

    // Don't forget about last blank row
    len = VGA_WIDTH;
    while (len--)
        *dst++ = make_vgaentry(FILLCHAR, terminal_color);
}

void terminal_initialize()
{
	uint16_t vga_entry;

    terminal_row = 0;
    terminal_column = 0;
	move_csr();

    terminal_color = make_color(COLOR_WHITE, COLOR_BLACK);
    terminal_buffer = (uint16_t *) VGA_BUFFER;

	vga_entry = make_vgaentry(FILLCHAR, terminal_color);
	memset16(terminal_buffer, vga_entry, VGA_WIDTH * VGA_HEIGHT);

    VGA_BUFFER_SIZE = VGA_WIDTH * VGA_HEIGHT;
}

void terminal_putchar(char c)
{
    if ( c == '\n' )
    {
        terminal_column = 0;
        if ( ++terminal_row == VGA_HEIGHT )
        {
            terminal_scroll();
            terminal_row--;
        }

		move_csr();
        return;
    }

    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if ( ++terminal_column == VGA_WIDTH )
    {
        terminal_column = 0;
        if ( ++terminal_row == VGA_HEIGHT )
        {
            terminal_scroll();
            terminal_row--;
        }
    }
	move_csr();
}

void terminal_writestring(const char* data)
{
    size_t len = strlen(data);
    for ( size_t i = 0; i < len; i++ )
        terminal_putchar(data[i]);
}
