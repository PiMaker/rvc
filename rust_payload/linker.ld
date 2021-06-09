OUTPUT_ARCH( "riscv" )

ENTRY( _start )

MEMORY
{
  ram (rwx) : ORIGIN = 0x80400000, LENGTH = 0x800000
}

SECTIONS
{
  .kernel : {
    *(.start_here)
    *(.text .text.*)
    *(.rodata .rodata.*)
    *(.data .data.*)
  } > ram

  .stack (NOLOAD) : {
    . = . + 0x20000;
    PROVIDE(_end_stack = .);
  } > ram

  .heap (NOLOAD) : {
    PROVIDE(_begin_heap = .);
    . = . + 0x40000;
    PROVIDE(_end_heap = .);
  } > ram

}
