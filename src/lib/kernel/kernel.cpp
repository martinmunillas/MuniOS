#include "../utils/textPrint.hpp"
#include "../utils/parsers/intToString.hpp"
#include "../utils/parsers/hexToString.hpp"
#include "../utils/IDT.hpp"
#include "keyboard.hpp"
#include "memoryMap.hpp"
#include "heap.hpp"

extern const char WelcomeText[];

extern "C" void _start()
{
    setCursorPosition(positionFromCoords(0, 0));
    printString(WelcomeText);
    initializeIDT();
    mainKeyboardHandler = KeyboardHandler;

    MemoryMapEntry **usableMemoryMaps = getUsableMemoryRegions();

    initializeHeap(0x100000, 0x100000);

    uint64 *testMemoryAddress = (uint64 *)aligned_alloc(0x4000, 0x08);
    printString("\n\r");
    printString(hexToString((uint64)testMemoryAddress));

    uint64 *testMemoryAddress2 = (uint64 *)malloc(0x4000);
    printString("\n\r");
    printString(hexToString((uint64)testMemoryAddress2));
}