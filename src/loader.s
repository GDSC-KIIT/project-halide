.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
	.align 4
    .long MAGIC
    .long FLAGS
    .long CHECKSUM


.section .bootstrap_stack, "aw", @nobits
stack_bottom:
	.skip 16384 # 16KiB
stack_top:

.section .bss, "aw", @nobits
	.align 4096
boot_page_directory:
	.skip 4096
boot_page_table1:
	.skip 4096

.section .multiboot.text
.global _start
.type _start, @function
_start:
	movl $(boot_page_table1-0xC0000000), %edi
	movl $0, %esi
	movl $1023, %ecx
1:
	cmpl $(_kernel_start-0xC0000000), %esi
	jl 2f
	cmpl $(_kernel_end-0xC0000000), %esi
	jge 3f
	movl %esi, %edx
	orl $0x003, %edx
	movl %edx, (%edi)

2:
	addl $4096, %esi
	addl $4, %edi
	loop 1b

3: 
	# map VGA memory to 0xC03FF000 as "present, writable"
	movl $(0x000B8000 | 0x003), boot_page_table1 - 0xC0000000 + 1023 * 4
	# Map the page table to both virtual addresses 0x00000000 and 0xC0000000.
	movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 0
	movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 768 * 4

	# Set cr3 to the address of the boot_page_directory.
	movl $(boot_page_directory - 0xC0000000), %ecx
	movl %ecx, %cr3

	# Enable paging and the write-protect bit.
	movl %cr0, %ecx
	orl $0x80010000, %ecx
	movl %ecx, %cr0

	# Jump to higher half with an absolute jump. 
	lea 4f, %ecx
	jmp *%ecx

.section .text
.extern k_main
.extern call_ctors
.global loader

4:
	movl $0, boot_page_directory + 0
	movl %cr3, %ecx
	movl %ecx, %cr3
    mov $stack_top, %esp
    call call_ctors
    push %eax
    push %ebx
    call k_main


_stop:
    cli
    hlt
    jmp _stop
