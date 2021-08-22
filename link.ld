OUTPUT_FORMAT(binary)

ENTRY (_start)

INPUT
(
    build/kernel_entry.o
    
    build/kernel.o
    build/keyboard.o
    build/memoryMap.o
    build/heap.o
    build/memory.o

    build/IDT.o
    build/IO.o
    build/textPrint.o

    build/intToString.o
    build/floatToString.o
    build/hexToString.o

    build/binaries.o
)

OUTPUT
(
    build/kernel.bin
)

SECTIONS
{
    . = 0x8000;

    .text : ALIGN(0x1000)
    {
        *(.text)
    }

    .idt BLOCK(0x1000) : ALIGN(0x1000)
    {
        _idt = .;
        . = . + 0x1000;
    }

    .data : ALIGN(0x1000)
    {
        *(.data)
    }

    .rodata : ALIGN(0x1000)
    {
        *(.rodata)
    }

    .bss : ALIGN(0x1000)
    {
        *(COMMON)
        *(.bss)
    }
}