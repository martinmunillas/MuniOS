#include "../utils/textPrint.cpp"
#include "../utils/parsers/intToString.cpp"
#include "../utils/IDT.cpp"
#include "keyboard.cpp"
#include "memoryMap.cpp"

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