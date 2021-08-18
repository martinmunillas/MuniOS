#pragma once
#include "../../include/typeDefs.h"
#include "../utils/textPrint.h"
#include "../utils/parsers/intToString.h"

struct MemoryMapEntry
{
    uint64 baseAddress;
    uint64 regionLength;
    uint32 regionType;
    uint32 extendedAttr;
};

extern uint8 memory_region_count;

extern uint8 usableMemoryRegionCount;

void printMemoryMap(MemoryMapEntry *memoryMap);

extern MemoryMapEntry **getUsableMemoryRegions();