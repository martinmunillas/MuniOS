#pragma once
#include "../../include/typeDefs.hpp"
#include "../utils/textPrint.hpp"
#include "../utils/parsers/intToString.hpp"

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