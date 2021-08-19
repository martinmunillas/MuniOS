#include "hexToString.hpp"

char hexOutput[128];
template <typename T>
const char *hexToString(T value)
{
    T *valPtr = &value;
    uint8 *ptr;
    uint8 tmp;
    uint8 size = (sizeof(T)) * 2 - 1;

    for (uint8 i = 0; i < size; i++)
    {
        ptr = ((uint8 *)valPtr + i);
        tmp = ((*ptr & 0xf0) >> 4);
        hexOutput[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : 48);
        tmp = ((*ptr & 0x0f));
        hexOutput[size - (i * 2 + 0)] = tmp + (tmp > 9 ? 55 : 48);
    }

    hexOutput[size + 1] = 0;
    return hexOutput;
}

const char *hexToString(uint8 value) { return hexToString<uint8>(value); }
const char *hexToString(uint16 value) { return hexToString<uint16>(value); }
const char *hexToString(uint32 value) { return hexToString<uint32>(value); }
const char *hexToString(uint64 value) { return hexToString<uint64>(value); }
const char *hexToString(char value) { return hexToString<char>(value); }
const char *hexToString(short value) { return hexToString<short>(value); }
const char *hexToString(int value) { return hexToString<int>(value); }
const char *hexToString(long value) { return hexToString<long>(value); }