#include "textPrint.hpp"

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

void printString(const char *str, uint8 color)
{
    uint8 *charPtr = (uint8 *)str;
    uint16 index = cursorPosition;
    while (*charPtr != 0)
    {
        switch (*charPtr)
        {
        // Jump Line
        case 0xa:
            index += VGA_WIDTH;
            break;
        // Return char
        case 0xd:
            index -= index % VGA_WIDTH;
            break;
        default:
            *(VGA_MEMORY + index * 2) = *charPtr;
            *(VGA_MEMORY + index * 2 + 1) = color;
            index++;
        }
        charPtr++;
    }
    setCursorPosition(index);
}

void printChar(char chr, uint8 color)
{
    *(VGA_MEMORY + cursorPosition * 2) = chr;
    *(VGA_MEMORY + cursorPosition * 2 + 1) = color;
    setCursorPosition(cursorPosition + 1);
}

void clearScreen(uint64 color)
{
    uint64 value = 0;
    value += color << 8;
    value += color << 24;
    value += color << 40;
    value += color << 56;

    for (uint64 *i = (uint64 *)VGA_MEMORY; i < (uint64 *)(VGA_MEMORY + 4000); i++)
    {
        *i = value;
    }
}