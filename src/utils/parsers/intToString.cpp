#pragma once
#include "../typeDefs.cpp"

char intOutput[128];
template <typename T>
char *intToString(T value)
{
    uint8 isNegative = 0;
    if (value < 0)
    {
        intOutput[0] = '-';
        isNegative = 1;
        value *= -1;
    }

    uint8 size = 0;
    uint64 sizeTester = (uint64)value;
    while (sizeTester / 10 > 0)
    {
        sizeTester /= 10;
        size++;
    }

    uint8 index = 0;
    uint64 newValue = (uint64)value;
    while (newValue / 10 > 0)
    {
        uint8 reminder = newValue % 10;
        newValue /= 10;
        intOutput[isNegative + size - index] = reminder + 48; // at 48 start the integers on the ascii table
        index++;
    }
    intOutput[isNegative + size - index] = newValue % 10 + 48;
    newValue /= 10;

    intOutput[isNegative + size + 1] = 0;
    return intOutput;
}