.set magic_number, 0x1BADB002
.set flags, (1<<0 | 1<<1)
.set checksum, -(magic_number + flags)

.section .multiboot
    .long magic_number
    .long flags
    .long checksum

.section .text
.extern k_main
.extern call_ctors
.global loader

loader:
    mov $kernel_stack, %esp
    call call_ctors
    push %eax
    push %ebx
    call k_main

halt:
    cli
    hlt
    jmp halt


.section .bss
.space 2*1024*1024; # 2 MiB
kernel_stack:
