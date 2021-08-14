#pragma once
#include "typeDefs.cpp"

void outb(uint16 port, uint8 val)
{
    asm volatile("outb %0, %1"
                 :
                 : "a"(val), "Nd"(port));
}

uint8 inb(uint16 port)
{
    uint8 val;
    asm volatile("inb %1, %0"
                 : "=a"(val)
                 : "Nd"(port));
    return val;
}
