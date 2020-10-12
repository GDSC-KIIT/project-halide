ENTRY (_start)

SECTIONS
{
    . = 0x00100000;
	/* The kernel will live at 3GB + 1MB in the virtual address space, */
	/* which will be mapped to 1MB in the physical address space. */
	/* Note that we page-align the sections. */
	.multiboot.text : {
    	*(.multiboot.text)
    }

	. += 0xC0000000;
	/* Add a symbol that indicates the start address of the kernel. */
	_kernel_start = .;
	.text ALIGN (4K) : AT (ADDR (.text) - 0xC0000000)
	{
		*(.multiboot)
		*(.text)
	}

	.rodata ALIGN (4K) : AT (ADDR (.rodata) - 0xC0000000)
	{
		*(.rodata)
	}
	
	.data ALIGN (4K) : AT (ADDR (.data) - 0xC0000000)
	{
		begin_constructors = .;
    	KEEP(*( .init_array ));
    	KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
    	end_constructors = .;
		*(.data)
	}
	
	.bss ALIGN (4K) : AT (ADDR (.bss) - 0xC0000000)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
	
	/* Add a symbol that indicates the end address of the kernel. */
	_kernel_end = .;
}