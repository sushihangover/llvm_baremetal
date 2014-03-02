OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")

ENTRY(Reset_Handler)

MEMORY
{
  flash (rx)  : ORIGIN = 0K, LENGTH = 64K
  sram  (rwx) : ORIGIN = 128K, LENGTH =  4K
}

_end_stack = 132K;

SECTIONS {
    . = ORIGIN(flash);

    vectors :
    {
        *(.vectors)
    } >flash

    .text :
    {
        *(.text)
        *(.rodata)
        *(.rodata*)
        _end_text = .;
    } >flash

    .data :
    {
        _start_data = .;
        *(.data)
        _end_data = .;
    } >sram AT >flash

    . = ALIGN(4);

    .bss :
    {
        _start_bss = .;
        *(.bss)
        _end_bss = .;
    } >sram

    . = ALIGN(4);

    heap_low = .; /* for _sbrk */
    . = . + 1K; /* 1kB of heap memory */
    heap_top = .; /* for _sbrk */

    _start_heap = .;
    PROVIDE( __cs3_heap_start = _start_heap);
	
    _start_stack = .;
}

_end = .;
PROVIDE(end = .);

