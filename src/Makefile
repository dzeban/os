export PATH := ../toolchain/cross/bin:$(PATH)

PREFIX := i686-elf
CC := $(PREFIX)-gcc
AS := $(PREFIX)-as
QEMU := qemu-system-i386

LINKER_SCRIPT := linker.ld

KERNEL_OPTS := -ffreestanding -O2
LINKER_OPTS := $(KERNEL_OPTS) -nostdlib -lgcc
COMPILER_OPTS := $(KERNEL_OPTS) -std=gnu99 -Wall -Wextra

default: kernel

vga.o: vga.c
	$(CC) -c $^ -o $@ $(COMPILER_OPTS)

lib.o: lib.c
	$(CC) -c $^ -o $@ $(COMPILER_OPTS)

kernel.o: kernel.c
	$(CC) -c $^ -o $@ $(COMPILER_OPTS)

boot.o: boot.s
	$(AS) $^ -o $@

kernel: kernel.o boot.o lib.o vga.o
	$(CC) -T $(LINKER_SCRIPT) $^ -o $@.bin $(LINKER_OPTS)

run: kernel
	$(QEMU) -kernel $<.bin

clean: 
	rm -f *.o *.bin
