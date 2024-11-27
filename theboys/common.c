#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "missao.h"
#include "heroi.h"
#include "base.h"

int aleat(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void erro(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

struct params_t *params_cria(struct heroi_t *h, struct base_t *b,
                             struct missao_t *m)
{
    struct params_t *p = malloc(sizeof(struct params_t));

    if (p == NULL)
        return NULL;

    p->h = h;
    p->b = b;
    p->m = m;

    return p;
}

void params_destroi(struct params_t **p)
{
    if (p == NULL || *p == NULL)
        return;

    free(*p);
    *p = NULL;
}
