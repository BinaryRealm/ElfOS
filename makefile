os_bin:
	nasm -f elf32 -o object_files/boot.o source/boot.asm
	nasm -f elf32 -o object_files/interrupt_wrappers.o source/interrupt_wrappers.asm
	clang -c -ffreestanding --target=i686-pc-none-elf -o object_files/kernel.o source/kernel.c
	clang -c -ffreestanding --target=i686-pc-none-elf -o object_files/vga.o source/vga.c
	clang -c -ffreestanding --target=i686-pc-none-elf -o object_files/gdt.o source/gdt.c
	clang -c -ffreestanding --target=i686-pc-none-elf -o object_files/idt.o source/idt.c
	clang -c -ffreestanding --target=i686-pc-none-elf -o object_files/isr.o source/isr.c
	ld.lld -T template.ld --nostdlib -o boot.bin object_files/boot.o object_files/kernel.o object_files/vga.o object_files/gdt.o object_files/idt.o object_files/interrupt_wrappers.o object_files/isr.o
	qemu-system-i386 -kernel boot.bin
