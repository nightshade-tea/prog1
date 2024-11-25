#include <stdlib.h>
#include "conjunto.h"
#include "common.h"
#include "ponto.h"
#include "mundo.h"
#include "fila.h"
#include "base.h"

void base_destroi(struct base_t **b)
{
    if (b == NULL || *b == NULL)
        return;

    (*b)->pres = cjto_destroi((*b)->pres);
    fila_destroi(&((*b)->esp));
    ponto_destroi(&((*b)->loc));

    free(*b);
    *b = NULL;
}

struct base_t *base_cria(int id)
{
    struct base_t *b = malloc(sizeof(struct base_t));

    if (b == NULL)
        return NULL;

    b->loc = ponto_cria(aleat(0, N_TAMANHO_MUNDO - 1),
                        aleat(0, N_TAMANHO_MUNDO - 1));

    b->lot = aleat(B_MIN_LOTACAO, B_MAX_LOTACAO);
    b->pres = cjto_cria(b->lot);
    b->esp = fila_cria();
    b->id = id;

    if (b->loc == NULL || b->esp == NULL || b->pres == NULL) {
        base_destroi(&b);
        return NULL;
    }

    return b;
}
