OUTPUT_ARCH( "riscv" )

ENTRY( _start )

MEMORY
{
  ram (rwx) : ORIGIN = 0x80000000, LENGTH = 0x100000
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
    . = . + 0x70000;
    PROVIDE(_end_stack = .);
  } > ram

  .heap (NOLOAD) : {
    . = . + 0x70000;
    PROVIDE(_end_heap = .);
  } > ram

  .textbuf (NOLOAD) : {
    . = . + 0x10000;
    PROVIDE(_end_textbuf = .);
  } > ram

}
