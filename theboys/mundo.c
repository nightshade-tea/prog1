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

struct heroi_t **vh_cria()
{
    struct heroi_t **vh = malloc(N_HEROIS * sizeof(struct heroi_t *));

    if (vh == NULL)
        return NULL;

    int i;
    for (i = 0; i < N_HEROIS; i++) {
        vh[i] = heroi_cria(i, NULL);

        if (vh[i] == NULL) {
            vh_destroi(&vh);
            return NULL;
        }
    }

    return vh;
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

struct base_t **vb_cria()
{
    struct base_t **vb = malloc(N_BASES * sizeof(struct base_t *));

    if (vb == NULL)
        return NULL;

    int i;
    for (i = 0; i < N_BASES; i++) {
        vb[i] = base_cria(i);

        if (vb[i] == NULL) {
            vb_destroi(&vb);
            return NULL;
        }
    }

    return vb;
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

struct missao_t **vm_cria()
{
    struct missao_t **vm = malloc(N_MISSOES * sizeof(struct missao_t *));

    if (vm == NULL)
        return NULL;

    int i;
    for (i = 0; i < N_MISSOES; i++) {
        vm[i] = missao_cria(i);

        if (vm[i] == NULL) {
            vm_destroi(&vm);
            return NULL;
        }
    }

    return vm;
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
    struct mundo_t *w = malloc(sizeof(struct mundo_t));

    if (w == NULL)
        return NULL;

    w->herois = vh_cria();
    w->bases = vb_cria();
    w->missoes = vm_cria();
    w->clk = T_INICIO;
    w->evs_tratados = 0;

    if (w->herois == NULL || w->bases == NULL || w->missoes == NULL) {
        mundo_destroi(&w);
        return NULL;
    }

    return w;
}

struct heroi_t *mundo_heroi(struct mundo_t *w, int id)
{
    if (w == NULL || w->herois == NULL || id < 0 || id >= N_HEROIS)
        return NULL;

    return w->herois[id];
}

struct base_t *mundo_base(struct mundo_t *w, int id)
{
    if (w == NULL || w->bases == NULL || id < 0 || id >= N_BASES)
        return NULL;

    return w->bases[id];
}

struct missao_t *mundo_missao(struct mundo_t *w, int id)
{
    if (w == NULL || w->missoes == NULL || id < 0 || id >= N_MISSOES)
        return NULL;

    return w->missoes[id];
}

int mundo_relogio(struct mundo_t *w)
{
    if (w == NULL)
        return -1;

    return w->clk;
}

int mundo_eventos_tratados(struct mundo_t *w)
{
    if (w == NULL)
        return -1;

    return w->evs_tratados;
}

void mundo_atualiza_relogio(struct mundo_t *w, int t)
{
    if (w == NULL || t < 0)
        return;

    w->clk = t;
    w->evs_tratados++;
}