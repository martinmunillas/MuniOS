#pragma once
#include "../utils/typeDefs.cpp"
#include "../utils/textPrint.cpp"
#include "../utils/parsers/intToString.cpp"

struct MemoryMapEntry
{
    uint64 baseAddress;
    uint64 regionLength;
    uint32 regionType;
    uint32 extendedAttr;
};

extern uint8 memory_region_count;

uint8 usableMemoryRegionCount = 0;
MemoryMapEntry *usableMemoryRegion[10];

void printMemoryMap(MemoryMapEntry *memoryMap)
{
    printString("\n\r");
    printString("Memory Base: ");
    printString(intToString(memoryMap->baseAddress));
    printString("\n\r");

    printString("Region Length: ");
    printString(intToString(memoryMap->regionLength));
    printString("\n\r");

    printString("Region Type: ");
    printString(intToString(memoryMap->regionType));
    printString("\n\r");

    printString("extended Attributes: ");
    printString(intToString(memoryMap->extendedAttr));
    printString("\n\r");
}

bool gotMemoryRegions = 0;

MemoryMapEntry **getUsableMemoryRegions()
{
    if (!gotMemoryRegions)
    {
        uint8 idx = 0;
        for (uint8 i = 0; i < memory_region_count; i++)
        {
            MemoryMapEntry *memMap = (MemoryMapEntry *)0x5000;
            memMap += i;
            if (memMap->regionType == 1)
            {
                usableMemoryRegion[idx] = memMap;
                idx++;
            };
        }
        usableMemoryRegionCount = idx;
        gotMemoryRegions = 1;
    };
    return usableMemoryRegion;
}