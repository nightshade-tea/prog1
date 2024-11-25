#include <stdlib.h>
#include <math.h>
#include "ponto.h"

struct ponto_t *ponto_cria(int x, int y)
{
    struct ponto_t *p = malloc(sizeof(struct ponto_t));

    if (p == NULL)
        return NULL;

    p->x = x;
    p->y = y;

    return p;
}

void ponto_destroi(struct ponto_t **p)
{
    if (p == NULL || *p == NULL)
        return;

    free(*p);
    *p = NULL;
}

int ponto_distancia(struct ponto_t *p, struct ponto_t *q)
{
    if (p == NULL || q == NULL)
        return -1;

    int dx = p->x - q->x;
    int dy = p->y - q->y;

    return round(hypot(dx, dy));
}
