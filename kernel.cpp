#include "textPrint.cpp"

extern "C" void _start()
{
    setCursorPosition(positionFromCoords(0, 0));
    printString("Hello World");
    return;
};