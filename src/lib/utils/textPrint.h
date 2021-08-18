#pragma once
#include "IO.h"
#include "../../include/typeDefs.h"
#include "../../include/textModeColorCodes.h"
#define VGA_MEMORY (uint8 *)0xb8000
#define VGA_WIDTH 80

extern uint16 cursorPosition;

void setCursorPosition(uint16 position);

uint16 positionFromCoords(uint8 x, uint8 y);

void printString(const char *str, uint8 color = BACKGROUND_BLINKINGYELLOW | FOREGROUND_BLACK);

void printChar(char chr, uint8 color = BACKGROUND_BLINKINGYELLOW | FOREGROUND_BLACK);

void clearScreen(uint64 color = BACKGROUND_BLINKINGYELLOW | FOREGROUND_BLACK);
