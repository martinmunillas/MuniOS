#include "keyboard.hpp"

bool shiftPressed = 0;
uint8 lastScanCode;

void KeyboardHandler(uint8 scanCode, uint8 chr)
{
    if (chr != 0)
    {
        if (shiftPressed)
        {
            printChar(chr - 32);
        }
        else
        {
            printChar(chr);
        }
    }
    else
    {
        switch (scanCode)
        {
        // backspace
        case 0x8e:
            setCursorPosition(cursorPosition - 1);
            printChar(' ');
            setCursorPosition(cursorPosition - 1);
            break;
        // left or right shift pressed
        case 0x2a:
        case 0x36:
            shiftPressed = 1;
            break;
        // left or right shift released
        case 0xb6:
        case 0xaa:
            shiftPressed = 0;
            break;
        // enter
        case 0x9c:
            printString("\n\r");
            break;
        default:
            break;
        }
    }
    lastScanCode = scanCode;
}