#pragma once
#include "../utils/typeDefs.cpp"

struct MemoryMapEntry
{
    uint64 baseAddress;
    uint64 regionLength;
    uint32 regionType;
    uint32 extendedAttr;
};

extern uint8 memory_region_count;