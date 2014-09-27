#include <stdint.h>

// This structure contains the value of one GDT entry.
struct gdt_entry
{
	uint16_t limit_low;           // The lower 16 bits of the limit.
	uint16_t base_low;            // The lower 16 bits of the base.
	uint8_t  base_middle;         // The next 8 bits of the base.
	uint8_t  access;              // Access flags, determine what ring this segment can be used in.
	uint8_t  flags_limit_high;
	uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed));

// Struct to tell CPU where to find GDT
struct gdt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

void gdt_init();
