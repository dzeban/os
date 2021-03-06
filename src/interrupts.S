.extern isr_handler

.global idt_flush
idt_flush:
	movl 4(%esp), %eax
	lidt (%eax)
	ret

isr_common_stub:
	pusha

	movw %ds, %ax # Save data segment descriptor
	pushl %eax

	movw $0x10, %ax # load kernel segment descriptor
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs

	call isr_handler

	popl %eax

	movw %ax, %ds # Reload original data segment descriptor
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs

	popa
	add $8, %esp # Clean up pushed error code
	sti
	iret

.macro ISR_NOERRCODE n  # define a macro, taking one parameter
.global isr\n
isr\n:
	cli
	pushl $0
	pushl $\n
	jmp isr_common_stub
.endm

.macro ISR_ERRCODE n
.global isr\n
isr\n:
	cli
	pushl \n
	jmp isr_common_stub
.endm

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

