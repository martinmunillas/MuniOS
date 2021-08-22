#include "memory.hpp"

void memset(void *start, uint64 value, uint64 size)
{
    if (size <= 8)
    {
        uint8 *valPtr = (uint8 *)&value;
        for (uint8 *ptr = (uint8 *)start; ptr < (uint8 *)((uint64)start + size); ptr++)
        {
            *ptr = *valPtr;
            valPtr++;
        }
        return;
    }

    uint64 proceedingBytes = size % 8;
    uint64 newSize = size - proceedingBytes;

    for (uint64 *ptr = (uint64 *)start; ptr < (uint64 *)((uint64)start + newSize); ptr++)
    {
        *ptr = value;
    }
    uint8 *valPtr = (uint8 *)&value;
    for (uint8 *ptr = (uint8 *)((uint64)start + newSize); ptr < (uint8 *)((uint64)start + size); ptr++)
    {
        *ptr = *valPtr;
        valPtr++;
    }
}

void memcpy(void *dest, void *src, uint64 size)
{
    if (size <= 8)
    {
        uint8 *valPtr = (uint8 *)src;
        for (uint8 *ptr = (uint8 *)dest; ptr < (uint8 *)((uint64)dest + size); ptr++)
        {
            *ptr = *valPtr;
            valPtr++;
        }
        return;
    }

    uint64 proceedingBytes = size % 8;
    uint64 newSize = size - proceedingBytes;
    uint64 *srcPtr = (uint64 *)src;

    for (uint64 *ptr = (uint64 *)dest; ptr < (uint64 *)((uint64)dest + newSize); ptr++)
    {
        *ptr = *srcPtr;
        srcPtr++;
    }
    uint8 *valPtr = (uint8 *)((uint64)src + newSize);
    for (uint8 *ptr = (uint8 *)((uint64)dest + newSize); ptr < (uint8 *)((uint64)dest + size); ptr++)
    {
        *ptr = *valPtr;
        valPtr++;
    }
}