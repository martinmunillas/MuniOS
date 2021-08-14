#pragma once
#include "IO.cpp"
#include "typeDefs.cpp"
#define VGA_MEMORY (uint8 *)0xb8000
#define VGA_WIDTH 80

uint16 cursorPosition;

void setCursorPosition(uint16 position)
{
    outb(0x3d4, 0x0f);
    outb(0x3d5, (uint8)(position & 0xff));
    outb(0x3d4, 0x0e);
    outb(0x3d5, (uint8)((position >> 0x8) & 0xff));

    cursorPosition = position;
}

uint16 positionFromCoords(uint8 x, uint8 y)
{
    return y * VGA_WIDTH + x;
}

void printString(const char *str)
{
    uint8 *charPtr = (uint8 *)str;
    uint16 index = cursorPosition;
    while (*charPtr != 0)
    {
        *(VGA_MEMORY + index * 2) = *charPtr;
        charPtr++;
        index++;
    }
    setCursorPosition(index);
}