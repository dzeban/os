.globl gdt_flush
gdt_flush:
	movl 4(%esp), %eax # Load argument
	lgdt (%eax) # Set GDT

	movw $16, %ax # Get GDT[2] (each GDT entry is 8 bytes)
	movw %ax, %ds # Load all data segment selectors
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss

	jmpl $0x08, $complete_flush # Reload CS

complete_flush:
	ret
