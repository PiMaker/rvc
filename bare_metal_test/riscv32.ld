MEMORY
{
    RAM : ORIGIN = 0x80000000, LENGTH = 60M
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        *(.entry)
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
    } >RAM

    .data :
    {
        . = ALIGN(4);
        *(.data)
        *(.data*)
    } >RAM

    .bss :
    {
        . = ALIGN(4);
        *(.bss)
        *(.bss*)
        *(COMMON)
    } >RAM
}
