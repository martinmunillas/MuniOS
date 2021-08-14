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
            index++;
        }
        charPtr++;
    }
    setCursorPosition(index);
}

char hexToStringOutput[128];
template <typename T>
const char *hexToString(T value)
{
    T *valPtr = &value;
    uint8 *ptr;
    uint8 tmp;
    uint8 size = (sizeof(T)) * 2 - 1;

    for (uint8 i = 0; i < size; i++)
    {
        ptr = ((uint8 *)valPtr + i);
        tmp = ((*ptr & 0xf0) >> 4);
        hexToStringOutput[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : 48);
        tmp = ((*ptr & 0x0f));
        hexToStringOutput[size - (i * 2 + 0)] = tmp + (tmp > 9 ? 55 : 48);
    }

    hexToStringOutput[size + 1] = 0;
    return hexToStringOutput;
}