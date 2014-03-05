OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")

ENTRY(Reset_Handler)

/* Specify the memory areas */
MEMORY
{
  FLASH (rx)      : ORIGIN = 0x00000000, LENGTH = 0x10000 /* 64K */
  RAM (xrw)       : ORIGIN = 0x00020000, LENGTH = 0x02000 /*  8K */
}

heap_size = 0x800; /* 2K */

SECTIONS {
    . = ORIGIN(FLASH);

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

        .ARM.extab : 
        {
                *(.ARM.extab* .gnu.linkonce.armextab.*)
        } > FLASH

        __exidx_start = .;
        .ARM.exidx :
        {
                *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        } > FLASH
        __exidx_end = .;

    _end_text = .;

    .data : AT (_end_text)
    {
        _start_data = .;
        *(.data)
        *(.data*) 
        . = ALIGN(4);
        _end_data = .;
    } >RAM 

    .bss :
    {
         . = ALIGN(4);
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
	__end__ = .;
        /* _heap_start = .; */
        /* "end" is used by newlib's syscalls!!! */
        PROVIDE(end = .);
        PROVIDE(_heap_start = end );
        . = . + heap_size;
        PROVIDE(_heap_end = .);
    } >RAM

    .ARM.attributes 0 : { *(.ARM.attributes) }

    .stack_dummy (COPY):
    {
	_end_stack = .;
        *(.stack*)
    } > RAM
    
    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack_dummy section */
    _start_stack = ORIGIN(RAM) + LENGTH(RAM);
    _size_stack = _start_stack - SIZEOF(.stack_dummy);
    PROVIDE(__stack = _start_stack);
        
    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(_size_stack >= _heap_end, "region RAM overflowed with stack")
}
_end = .;

