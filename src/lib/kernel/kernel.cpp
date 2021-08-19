#include "../utils/textPrint.hpp"
#include "../utils/parsers/intToString.hpp"
#include "../utils/IDT.hpp"
#include "keyboard.hpp"
#include "memoryMap.hpp"

extern const char WelcomeText[];

extern "C" void _start()
{
    setCursorPosition(positionFromCoords(0, 0));
    printString(WelcomeText);
    initializeIDT();
    mainKeyboardHandler = KeyboardHandler;

    MemoryMapEntry **usableMemoryMaps = getUsableMemoryRegions();

    for (int i = 0; i < usableMemoryRegionCount; i++)
    {
        MemoryMapEntry *memMap = usableMemoryMaps[i];
        printMemoryMap(memMap);
    }
}