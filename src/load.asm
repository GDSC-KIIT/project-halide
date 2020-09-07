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
    hlt
