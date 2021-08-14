#include "../utils/textPrint.cpp"

extern "C" void _start()
{
    setCursorPosition(positionFromCoords(0, 0));
    printString("\n\r Hello World\n\r\n\r Welcome To MuniOS");
    return;
};