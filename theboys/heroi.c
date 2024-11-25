#include <stdlib.h>
#include "conjunto.h"
#include "common.h"
#include "heroi.h"

void heroi_destroi(struct heroi_t **heroi)
{
    if (heroi == NULL || *heroi == NULL)
        return;

    (*heroi)->habilidades = cjto_destroi((*heroi)->habilidades);

    free(*heroi);
    *heroi = NULL;
}

struct heroi_t *heroi_cria(int id, int base)
{
    struct heroi_t *heroi = malloc(sizeof(struct heroi_t));

    if (heroi == NULL)
        return NULL;

    heroi->habilidades = cjto_cria(aleat(H_MIN_HABILIDADES, H_MAX_HABILIDADES));

    if (heroi->habilidades == NULL) {
        heroi_destroi(&heroi);
        return NULL;
    }

    heroi->id = id;
    heroi->base = base;
    heroi->experiencia = H_EXPERIENCIA_INICIAL;
    heroi->paciencia = aleat(H_MIN_PACIENCIA, H_MAX_PACIENCIA);
    heroi->velocidade = aleat(H_MIN_VELOCIDADE, H_MAX_VELOCIDADE);

    return heroi;
}
