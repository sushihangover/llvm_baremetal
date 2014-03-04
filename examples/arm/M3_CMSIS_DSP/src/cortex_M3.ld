OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")

ENTRY(Reset_Handler)

/* Specify the memory areas */
MEMORY
{
  FLASH (rx)      : ORIGIN = 0x00000000, LENGTH = 0x10000 /*64K*/
  RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 0x02000 /*8K*/
}

stack_size = 512;
heap_size = 256;

SECTIONS {
    . = ORIGIN(flash);

    .vectors :
    {
        . = ALIGN(4);
        KEEP(*(.vectors)) /* Startup code */
        . = ALIGN(4);
    } >FLASH

    .text :
    {
        . = ALIGN(4);
        _start_text = .;
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        _end_text = .;
    } >FLASH

    .data :
    {
        . = ALIGN(4);
        _start_data = .;
        *(.data)
        *(.data*)
        _end_data = .;
    } >RAM AT >FLASH

    . = ALIGN(4);
    .bss :
    {
        _start_bss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _end_bss = .;
    } >RAM

    . = ALIGN(4);
    .heap :
    {
        _heap_start = .;
        . = . + heap_size;
                _heap_end = .;
    } >RAM
 
    /* Remove information from the standard libraries */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }
 
    .ARM.attributes 0 : { *(.ARM.attributes) }

    _end_stack = _stack_start - stack_size;
    _start_stack = ORIGIN(RAM)+LENGTH(RAM);
}

_end = .;
PROVIDE(end = .);

