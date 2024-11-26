#include <stdlib.h>
#include "conjunto.h"
#include "common.h"
#include "mundo.h"
#include "heroi.h"

void heroi_destroi(struct heroi_t **h)
{
    if (h == NULL || *h == NULL)
        return;

    (*h)->habs = cjto_destroi((*h)->habs);

    free(*h);
    *h = NULL;
}

struct heroi_t *heroi_cria(int id, int base)
{
    struct heroi_t *h = malloc(sizeof(struct heroi_t));

    if (h == NULL)
        return NULL;

    h->habs = cjto_aleat(aleat(H_MIN_HABILIDADES, H_MAX_HABILIDADES),
                         N_HABILIDADES);

    if (h->habs == NULL) {
        heroi_destroi(&h);
        return NULL;
    }

    h->id = id;
    h->base = base;
    h->exp = H_EXPERIENCIA_INICIAL;
    h->pac = aleat(H_MIN_PACIENCIA, H_MAX_PACIENCIA);
    h->vel = aleat(H_MIN_VELOCIDADE, H_MAX_VELOCIDADE);

    return h;
}
