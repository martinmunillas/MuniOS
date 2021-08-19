#pragma once
#include "../../include/typeDefs.hpp"
#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xa0
#define PIC2_DATA 0xa1

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

void outb(uint16 port, uint8 val);

uint8 inb(uint16 port);

void remapPic();