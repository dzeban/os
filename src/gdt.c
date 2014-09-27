#include "gdt.h"

extern void gdt_flush(uint32_t);

struct gdt_entry GDT[5];
struct gdt_ptr gdt_ptr;

static void gdt_set_gate(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	GDT[num].base_low    = (base & 0xFFFF);
	GDT[num].base_middle = (base >> 16) & 0xFF;
	GDT[num].base_high   = (base >> 24) & 0xFF;

	GDT[num].access = access;

	GDT[num].limit_low = limit & 0xFFFF;
	GDT[num].flags_limit_high = (limit >> 16) & 0x0F;
	GDT[num].flags_limit_high |= (flags) & 0xF0;
}

void gdt_init()
{
	gdt_ptr.base = (uint32_t *)&GDT;
	gdt_ptr.limit = sizeof(GDT) - 1;

	// Setup flat model with 4 segments
	gdt_set_gate(0, 0, 0, 0, 0); // Required null segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel code
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel data
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User code
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User data

	gdt_flush((uint32_t)&gdt_ptr);
}
