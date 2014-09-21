// These headers are freestanding
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "lib.h"
#include "vga.h"

// Check if the compiler thinks if we are targeting the wrong operating system.
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

// This tutorial will only work for the 32-bit ix86 targets.
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main()
{
    terminal_initialize();
    for ( size_t y = 0; y < VGA_HEIGHT; y++ )
    {
        terminal_putchar(y%10 + '0');
        terminal_writestring("Hello, kernel World!\n");
    }

    terminal_writestring("Scroll, yeah!\n");
    terminal_writestring("Scroll, yeah 2!\n");
}
