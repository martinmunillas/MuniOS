#pragma once
#include "../../include/typeDefs.hpp"
#include "memory.hpp"

struct MemorySegmentHeader
{
    uint64 memoryLength;
    MemorySegmentHeader *nextSegment;
    MemorySegmentHeader *prevSegment;
    MemorySegmentHeader *nextFreeSegment;
    MemorySegmentHeader *prevFreeSegment;
    bool free;
};

struct AlignedMemorySegmentHeader
{
    uint64 memorySegmentHeaderAddress : 63;
    bool isAligned : 1;
};

void initializeHeap(uint64 heapAddress, uint64 heapLength);

void *malloc(uint64 size);

void *calloc(uint64 size);
void *calloc(uint64 num, uint64 size);

void *realloc(void *address, uint64 size);

void *aligned_alloc(uint64 alignment, uint64 size);

void free(void *address);