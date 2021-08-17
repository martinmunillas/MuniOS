#include "../typeDefs.cpp"
#include "intToString.cpp"

char floatOutput[128];
const char *floatToString(float value, uint8 decimalPlaces = 1)
{
    char *intPtr = (char *)intToString((int)value);
    char *floatPtr = floatOutput;

    if (value < 0)
    {
        value *= -1;
    }

    while (*intPtr != 0)
    {
        *floatPtr = *intPtr;
        intPtr++;
        floatPtr++;
    }
    *floatPtr = '.';
    floatPtr++;

    float newValue = value - (int)value;

    for (uint8 i = 0; i < decimalPlaces; i++)
    {
        newValue *= 10;
        *floatPtr = (int)newValue + 48;
        floatPtr++;
        newValue -= (int)newValue;
    }

    *floatPtr = 0;

    return floatOutput;
}