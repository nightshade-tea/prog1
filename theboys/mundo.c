#include <stdlib.h>
#include "missao.h"
#include "mundo.h"
#include "heroi.h"
#include "base.h"

void vh_destroi(struct heroi_t ***vh)
{
    if (vh == NULL || *vh == NULL)
        return;

    int i;
    for (i = 0; i < N_HEROIS; i++)
        heroi_destroi(*vh + i);

    free(*vh);
    *vh = NULL;
}

void vb_destroi(struct base_t ***vb)
{
    if (vb == NULL || *vb == NULL)
        return;

    int i;
    for (i = 0; i < N_BASES; i++)
        base_destroi(*vb + i);

    free(*vb);
    *vb = NULL;
}

void vm_destroi(struct missao_t ***vm)
{
    if (vm == NULL || *vm == NULL)
        return;

    int i;
    for (i = 0; i < N_MISSOES; i++)
        missao_destroi(*vm + i);

    free(*vm);
    *vm = NULL;
}

void mundo_destroi(struct mundo_t **w)
{
    if (w == NULL || *w == NULL)
        return;

    vh_destroi(&((*w)->herois));
    vb_destroi(&((*w)->bases));
    vm_destroi(&((*w)->missoes));

    free(*w);
    *w = NULL;
}

struct mundo_t *mundo_cria()
{
    // TODO
}
