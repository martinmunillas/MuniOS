#pragma once
#include "../../include/typeDefs.h"
#include "IO.h"
#include "textPrint.h"
#include "./parsers/hexToString.h"
#include "../../include/KeyboardScanCodeSet1.h"

struct IDT64
{
    uint16 offsetLow;
    uint16 selector;
    uint8 ist;
    uint8 typesAttr;
    uint16 offsetMid;
    uint32 offsetHigh;
    uint32 zero;
};

void initializeIDT();

extern void (*mainKeyboardHandler)(uint8 scanCide, uint8 chr);