#include "heap.hpp"

MemorySegmentHeader *firstFreeMemorySegment;

void initializeHeap(uint64 heapAddress, uint64 heapLength)
{
    firstFreeMemorySegment = (MemorySegmentHeader *)heapAddress;
    firstFreeMemorySegment->memoryLength = heapLength - sizeof(MemorySegmentHeader);
    firstFreeMemorySegment->nextSegment = 0;
    firstFreeMemorySegment->prevSegment = 0;
    firstFreeMemorySegment->nextFreeSegment = 0;
    firstFreeMemorySegment->prevFreeSegment = 0;
    firstFreeMemorySegment->free = 1;
}

void *malloc(uint64 size)
{
    uint64 reminder = size % 8;
    size -= reminder;

    if (reminder != 0)
        size += reminder;

    MemorySegmentHeader *currentMemorySegment = firstFreeMemorySegment;
    while (true)
    {
        if (currentMemorySegment->memoryLength >= size)
        {
            if (currentMemorySegment->memoryLength > size + sizeof(MemorySegmentHeader))
            {
                MemorySegmentHeader *newSegmentHeader = (MemorySegmentHeader *)((uint64)currentMemorySegment + sizeof(MemorySegmentHeader) + size);

                newSegmentHeader->free = 1;
                newSegmentHeader->memoryLength = ((uint64)currentMemorySegment->memoryLength) - (sizeof(MemorySegmentHeader) + size);
                newSegmentHeader->nextFreeSegment = currentMemorySegment->nextFreeSegment;
                newSegmentHeader->nextSegment = currentMemorySegment->nextSegment;
                newSegmentHeader->prevSegment = currentMemorySegment;
                newSegmentHeader->prevFreeSegment = currentMemorySegment->prevFreeSegment;

                currentMemorySegment->nextFreeSegment = newSegmentHeader;
                currentMemorySegment->nextSegment = newSegmentHeader;
                currentMemorySegment->memoryLength = size;
            }
            if (currentMemorySegment == firstFreeMemorySegment)
            {
                firstFreeMemorySegment = currentMemorySegment->nextFreeSegment;
            }
            currentMemorySegment->free = 0;
            currentMemorySegment->memoryLength = size;

            if (currentMemorySegment->prevFreeSegment != 0)
                currentMemorySegment->prevFreeSegment->nextFreeSegment = currentMemorySegment->nextFreeSegment;

            if (currentMemorySegment->nextFreeSegment != 0)
                currentMemorySegment->nextFreeSegment->prevFreeSegment = currentMemorySegment->prevFreeSegment;

            if (currentMemorySegment->prevSegment != 0)
                currentMemorySegment->prevSegment->nextFreeSegment = currentMemorySegment->nextFreeSegment;

            if (currentMemorySegment->nextSegment != 0)
                currentMemorySegment->nextSegment->prevFreeSegment = currentMemorySegment->prevFreeSegment;

            return currentMemorySegment +
                   1;
        }
        if (currentMemorySegment->nextFreeSegment = 0)
        {
            return 0; //No memory remaining
        }
        currentMemorySegment = currentMemorySegment->nextFreeSegment;
        return 0;
    }
}

void *calloc(uint64 size)
{
    void *mallocVal = malloc(size);
    memset(mallocVal, 0, size);
    return mallocVal;
}

void *calloc(uint64 num, uint64 size)
{
    return calloc(num * size);
}

void *realloc(void *address, uint64 size)
{
    MemorySegmentHeader *oldSegmentHeader;

    AlignedMemorySegmentHeader *AMSH = (AlignedMemorySegmentHeader *)address - 1;
    if (AMSH->isAligned)
    {
        oldSegmentHeader = (MemorySegmentHeader *)(uint64)AMSH->memorySegmentHeaderAddress;
    }
    else
    {

        oldSegmentHeader = ((MemorySegmentHeader *)address) - 1;
    }

    uint64 smallerSize = oldSegmentHeader->memoryLength < size ? oldSegmentHeader->memoryLength : size;
    void *newMem = malloc(size);
    memcpy(newMem, address, smallerSize);
    free(address);
    return newMem;
}

void *aligned_alloc(uint64 alignment, uint64 size)
{
    uint64 alignmentReminder = alignment % 8;
    alignment -= alignmentReminder;
    if (alignmentReminder != 0)
        alignment += 8;

    uint64 sizeReminder = size % 8;
    size -= sizeReminder;
    if (sizeReminder != 0)
        size += 8;

    uint64 fullSize = size + alignment;
    void *mallocVal = malloc(fullSize);
    uint64 address = (uint64)mallocVal;

    uint64 reminder = address % alignment;
    address -= reminder;
    if (reminder != 0)
    {
        address += alignment;

        AlignedMemorySegmentHeader *AMSH = (AlignedMemorySegmentHeader *)address - 1;
        AMSH->isAligned = 1;
        AMSH->memorySegmentHeaderAddress = (uint64)mallocVal - sizeof(MemorySegmentHeader);
    }

    return (void *)address;
}

void combineFreeSegments(MemorySegmentHeader *a, MemorySegmentHeader *b)
{
    if (a == 0 || b == 0)
        return;
    if (a < b)
    {
        a->memoryLength += b->memoryLength + sizeof(MemorySegmentHeader);
        a->nextSegment = b->nextSegment;
        a->nextFreeSegment = b->nextFreeSegment;
        b->nextSegment->prevSegment = a;
        b->nextSegment->prevFreeSegment = a;
        b->nextFreeSegment->prevFreeSegment = a;
    }
    else
    {
        b->memoryLength += a->memoryLength + sizeof(MemorySegmentHeader);
        b->nextSegment = a->nextSegment;
        b->nextFreeSegment = a->nextFreeSegment;
        a->nextSegment->prevSegment = b;
        a->nextSegment->prevFreeSegment = b;
        a->nextFreeSegment->prevFreeSegment = b;
    }
}

void free(void *address)
{
    MemorySegmentHeader *currentMemorySegment;

    AlignedMemorySegmentHeader *AMSH = (AlignedMemorySegmentHeader *)address - 1;
    if (AMSH->isAligned)
    {
        currentMemorySegment = (MemorySegmentHeader *)(uint64)AMSH->memorySegmentHeaderAddress;
    }
    else
    {

        currentMemorySegment = ((MemorySegmentHeader *)address) - 1;
    }
    currentMemorySegment->free = true;

    if (currentMemorySegment < firstFreeMemorySegment)
        firstFreeMemorySegment = currentMemorySegment;

    if (currentMemorySegment->nextFreeSegment != 0)
    {
        if (currentMemorySegment->nextFreeSegment->prevFreeSegment < currentMemorySegment)
            currentMemorySegment->nextFreeSegment->prevFreeSegment = currentMemorySegment;
    }
    if (currentMemorySegment->prevFreeSegment != 0)
    {
        if (currentMemorySegment->prevFreeSegment->nextFreeSegment > currentMemorySegment)
            currentMemorySegment->prevFreeSegment->nextFreeSegment = currentMemorySegment;
    }

    if (currentMemorySegment->nextSegment != 0)
    {
        currentMemorySegment->nextSegment->prevSegment = currentMemorySegment;
        if (currentMemorySegment->nextSegment->free)
            combineFreeSegments(currentMemorySegment, currentMemorySegment->nextSegment);
    }
    if (currentMemorySegment->prevSegment != 0)
    {
        currentMemorySegment->prevSegment->nextSegment = currentMemorySegment;
        if (currentMemorySegment->prevSegment->free)
            combineFreeSegments(currentMemorySegment, currentMemorySegment->prevSegment);
    }
}