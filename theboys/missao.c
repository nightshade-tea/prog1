#include <stdlib.h>
#include "conjunto.h"
#include "common.h"
#include "missao.h"
#include "ponto.h"
#include "mundo.h"

void missao_destroi(struct missao_t **m)
{
    if (m == NULL || *m == NULL)
        return;

    (*m)->habs = cjto_destroi((*m)->habs);
    ponto_destroi(&((*m)->loc));

    free(*m);
    *m = NULL;
}

struct missao_t *missao_cria(int id)
{
    struct missao_t *m = malloc(sizeof(struct missao_t));

    if (m == NULL)
        return NULL;

    m->loc = ponto_cria(aleat(0, N_TAMANHO_MUNDO - 1),
                        aleat(0, N_TAMANHO_MUNDO - 1));

    m->habs = cjto_aleat(aleat(M_MIN_HABILIDADES, M_MAX_HABILIDADES),
                         N_HABILIDADES);

    m->per = aleat(M_MIN_PERIGO, M_MAX_PERIGO);
    m->id = id;

    if (m->loc == NULL || m->habs == NULL) {
        missao_destroi(&m);
        return NULL;
    }

    return m;
}
