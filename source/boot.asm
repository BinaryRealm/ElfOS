SECTION .multiboot align=4

MAGIC equ 0x1BADB002
FLAG equ 0x00000000
magic: dd MAGIC
flags: dd 0
checksum: dd -(MAGIC+FLAG)

SECTION .text

extern kernel_main
global _start
_start:
mov esp, stack_top
call kernel_main


;INFORMATION FOR PS2 CONTROLLER
;Data Port: 0x60 (Read or Write)
;Command Port: 0x64 (Write a command) or (Read the status register)
;
;
;
;
;
;
;
;




extern print_hexint
extern vga_newline
xor eax, eax

mov al, 0x60;set command byte
out 0x64, al
mov al, 0b00110101
out 0x60, al

mov al, 0x20;read command byte
out 0x64, al
in al, 0x60
push eax
call print_hexint
add esp, 4
call vga_newline

xor eax, eax
mov al, 0xAE; enable port 1
out 0x64, al
;in al, 0x60
;push eax
;call print_hexint
;add esp, 4
;call vga_newline


xor eax, eax
mov al, 0xAB; test port 1
out 0x64, al
in al, 0x60
push eax
call print_hexint
add esp, 4
call vga_newline



xor eax, eax
mov al, 0xEE ;keyboard echo works
out 0x60, al
in al, 0x60
push eax
call print_hexint
add esp, 4
call vga_newline

xor eax, eax
mov al, 0xF2; determine keyboard type
out 0x60, al
in al, 0x60
push eax
call print_hexint
add esp, 4
call vga_newline
in al, 0x60
push eax
call print_hexint
add esp, 4
call vga_newline
in al, 0x60
push eax
call print_hexint
add esp, 4
call vga_newline





xor eax, eax
mov al, 0xF4 ;enable scanning
out 0x60, al
in al, 0x60
push eax
call print_hexint
add esp, 4
call vga_newline
xor eax, eax
mov al, 0xF6 ;keyboard reset
out 0x60, al
in al, 0x60
push eax
call print_hexint
add esp, 4
call vga_newline

end:
;hlt
jmp end

;share this function to kernel.c and get location of data to share
global init_and_activate_gdt
extern my_lgdt_data

init_and_activate_gdt:
lgdt [my_lgdt_data]
mov cx, 0x10
mov ds,cx ;(13index)(1ti)(2rpl)
mov es,cx
mov fs,cx
mov gs,cx
mov ss,cx
jmp 0x8:reload_cs
reload_cs:
ret

global init_and_activate_idt
extern my_lidt_data

init_and_activate_idt:
lidt [my_lidt_data]
ret





SECTION .data

SECTION .bss align=16

stack_bottom:
resb 16384
stack_top:
