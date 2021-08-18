#include "../utils/textPrint.h"
#include "../utils/parsers/intToString.h"
#include "../utils/IDT.h"
#include "keyboard.h"
#include "memoryMap.h"

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