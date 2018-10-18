
/*
 Copyright Juan Manuel Gómez
*/

/* Linker script for ATSAM4SD32C ARM(R) Cortex(TM)-M4 MCU */

INPUT(libc.a libgcc.a libm.a)

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/* The beginning and end of the program ROM area */
/* Set up a ROM area with a size of 32K - 4 */
_rom_begin = 0x00400000;
_rom_end   = 0x00600000;

/* The beginning and end (i.e., the top) of the stack */
/* Set up a stack with a size of 4K */
_stack_begin = 0x20027000;
_stack_end   = 0x20028000;

__initial_stack_pointer = 0x20028000;


MEMORY
{
  ROM(rx)  : ORIGIN = 0x00400000, LENGTH = 0x00200000
  RAM(rwx) : ORIGIN = 0x20000000, LENGTH = 0x00027000
}

SECTIONS
{
  . = 0x00400000;
  . = ALIGN(4);

  /* ISR vectors */
  .isr_vector :
  {
    *(.isr_vector)
    . = ALIGN(0x10);
    KEEP(*(.isr_vector))
  } > ROM = 0xAAAA

  /* Program code (text), read-only data and static ctors */
  .text :
  {
    _ctors_begin = .;
    *(.init_array)
    . = ALIGN(4);
    KEEP (*(SORT(.init_array)))
    _ctors_end = .;
    *(.progmem*)
    . = ALIGN(2);
    *(.text)
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
    *(.rodata)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
  } > ROM

  .text :
  {
    . = ALIGN(0x10);
  } > ROM = 0xAAAA

  . = 0x20000000;
  . = ALIGN(4);

  /* The ROM-to-RAM initialized data section */
  .data :
  {
    _data_begin = .;
    *(.data)
    . = ALIGN(4);
    KEEP (*(.data))
    *(.data*)
    . = ALIGN(4);
    KEEP (*(.data*))
    _data_end = .;
  } > RAM AT > ROM

  /* The uninitialized (zero-cleared) data section */
  .bss :
  {
    _bss_begin = .;
    *(.bss)
    . = ALIGN(4);
    KEEP (*(.bss))
    *(.bss*)
    . = ALIGN(4);
    KEEP (*(.bss*))
    _bss_end = .;
  } > RAM

  _rom_data_begin = LOADADDR(.data);
}
