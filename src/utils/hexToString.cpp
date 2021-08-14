#include "typeDefs.cpp"

char hexToStringOutput[128];
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
        hexToStringOutput[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : 48);
        tmp = ((*ptr & 0x0f));
        hexToStringOutput[size - (i * 2 + 0)] = tmp + (tmp > 9 ? 55 : 48);
    }

    hexToStringOutput[size + 1] = 0;
    return hexToStringOutput;
}