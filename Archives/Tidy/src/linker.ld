
ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

SECTIONS
{
  . = 0x0100000;

  .text :
  {
    *(.multiboot)
    *(.text*)
    *(.rodata)
  }

  .data  :
  {
    begin_constructors = .;
    KEEP(*( .init_array ));
    KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
    end_constructors = .;

    *(.data)
  }

  .bss  :
  {
    *(.bss)
  }

  /DISCARD/ : { *(.fini_array*) *(.comment) }
}