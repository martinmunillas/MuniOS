#pragma once
#include "typeDefs.cpp"
#include "IO.cpp"
#include "textPrint.cpp"
#include "hexToString.cpp"
#include "numberToString.cpp"
#include "KeyboardScanCodeSet1.cpp"

struct IDT64
{
    uint16 offset_low;
    uint16 selector;
    uint8 ist;
    uint8 types_attr;
    uint16 offset_mid;
    uint32 offset_high;
    uint32 zero;
};

extern IDT64 _idt[256];
extern uint64 isr1;
extern "C" void load_idt();

void initializeIDT()
{
    _idt[1].zero = 0;
    _idt[1].offset_low = (uint16)((uint64)&isr1 & 0xffff);
    _idt[1].offset_low = (uint16)(((uint64)&isr1 & 0xffff0000) >> 16);
    _idt[1].offset_high = (uint32)(((uint64)&isr1 & 0xffffffff00000000) >> 32);
    _idt[1].ist = 0;
    _idt[1].selector = 0x8;
    _idt[1].types_attr = 0x8e;

    remapPic();

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    load_idt();
}

void (*mainKeyboardHandler)(uint8 scanCide, uint8 chr);

extern "C" void isr1Handler()
{
    printString(hexToString(inb(0x60)));
    uint8 scanCode = inb(0x60);
    uint8 chr = 0;
    if (scanCode < 0x3a)
    {
        chr = ScanCodeLookupTable[scanCode];
    }
    if (mainKeyboardHandler != 0)
    {
        mainKeyboardHandler(scanCode, chr);
    }
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}