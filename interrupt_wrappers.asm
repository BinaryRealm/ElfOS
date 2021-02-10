;maybe there is a better solution, but good enough for now
section .text

extern routine0
wrapper0:
pushad
call routine0
popad
mov al, 0x20
out 0x20,al
iret

extern routine1
wrapper1:
pushad
call routine1
popad
iret

extern routine2
wrapper2:
pushad
call routine2
popad
iret


section .data

;set up pointers to functions

global isr0
isr0: dd wrapper0
global isr1
isr1: dd wrapper1
global isr2
isr2: dd wrapper2
