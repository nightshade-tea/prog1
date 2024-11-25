#include <stdlib.h>

int aleat(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
