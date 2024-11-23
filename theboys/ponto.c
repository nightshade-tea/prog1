#include <stdlib.h>
#include <math.h>
#include "ponto.h"

struct ponto_t *ponto_cria(int x, int y)
{
    struct ponto_t *ponto = malloc(sizeof(struct ponto_t));

    if (ponto == NULL)
        return NULL;

    ponto->x = x;
    ponto->y = y;

    return ponto;
}

void ponto_destroi(struct ponto_t **ponto)
{
    if (ponto == NULL || *ponto == NULL)
        return;

    free(*ponto);
    *ponto = NULL;
}

int ponto_distancia(struct ponto_t *P, struct ponto_t *Q)
{
    if (P == NULL || Q == NULL)
        return -1;

    int dx = P->x - Q->x;
    int dy = P->y - Q->y;

    return round(hypot(dx, dy));
}
