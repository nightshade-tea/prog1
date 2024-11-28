#include <stdlib.h>
#include <stdio.h>
#include "common.h"

int aleat(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void erro(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
}