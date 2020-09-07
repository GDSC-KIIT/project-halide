bits 32
section .text
    align 4
    dd 0x1BADB002
    dd 0x00
    dd -(0x1BADB002+0x00)

global start
extern k_main
extern call_ctors
global load
load:
    cli
    call k_main
    call shutdown
    hlt

shutdown:
  mov ax, 0x1000
  mov ax, ss
  mov sp, 0xf000
  mov ax, 0x5307
  mov bx, 0x0001
  mov cx, 0x0003
  int 0x15
 
  ret  ;if interrupt doesnt work