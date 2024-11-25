#include <stdlib.h>
#include "conjunto.h"
#include "common.h"
#include "ponto.h"
#include "mundo.h"
#include "fila.h"
#include "base.h"

void base_destroi(struct base_t **base)
{
    if (base == NULL || *base == NULL)
        return;

    (*base)->presentes = cjto_destroi((*base)->presentes);
    fila_destroi(&((*base)->espera));
    ponto_destroi(&((*base)->local));

    free(*base);
    *base = NULL;
}

struct base_t *base_cria(int id)
{
    struct base_t *base = malloc(sizeof(struct base_t));

    if (base == NULL)
        return NULL;

    base->local = ponto_cria(aleat(0, N_TAMANHO_MUNDO - 1),
                             aleat(0, N_TAMANHO_MUNDO - 1));
    base->lotacao = aleat(B_MIN_LOTACAO, B_MAX_LOTACAO);
    base->presentes = cjto_cria(base->lotacao);
    base->espera = fila_cria();
    base->id = id;

    if (base->local == NULL || base->espera == NULL ||
        base->presentes == NULL) {
        base_destroi(&base);
        return NULL;
    }

    return base;
}
