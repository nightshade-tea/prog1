#include <stddef.h>
#include "conjunto.h"
#include "eventos.h"
#include "common.h"
#include "missao.h"
#include "mundo.h"
#include "ponto.h"
#include "fprio.h"
#include "heroi.h"
#include "base.h"
#include "fila.h"

void chega(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
    if (h == NULL || b == NULL || lef == NULL)
        return;

    h->base = b->id;

    int espera;
    if (cjto_card(b->pres) < b->lot && fila_tamanho(b->esp) == 0)
        espera = 1;
    else
        espera = (h->pac) > (10 * fila_tamanho(b->esp));

    struct params_t *p = params_cria(h, b, NULL);

    if (p == NULL)
        return;

    if (espera)
        fprio_insere(lef, p, EV_ESPERA, t);
    else
        fprio_insere(lef, p, EV_DESISTE, t);
}

void espera(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
    if (h == NULL || b == NULL || lef == NULL)
        return;

    fila_insere(b->esp, h);

    struct params_t *p = params_cria(NULL, b, NULL);

    if (p == NULL)
        return;

    fprio_insere(lef, p, EV_AVISA, t);
}

void desiste(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef,
             struct mundo_t *w)
{
    if (h == NULL || b == NULL || lef == NULL || w == NULL)
        return;

    struct params_t *p = params_cria(h, w->bases[aleat(0, N_BASES - 1)], NULL);

    if (p == NULL)
        return;

    fprio_insere(lef, p, EV_VIAJA, t);
}

void avisa(int t, struct base_t *b, struct fprio_t *lef)
{
    if (b == NULL || lef == NULL)
        return;

    while (cjto_card(b->pres) < b->lot && fila_tamanho(b->esp) > 0) {
        struct heroi_t *h = fila_retira(b->esp);
        struct params_t *p = params_cria(h, b, NULL);

        if (h != NULL && p != NULL) {
            cjto_insere(b->pres, h->id);
            fprio_insere(lef, p, EV_ENTRA, t);
        } else {
            params_destroi(&p);
        }
    }
}

void entra(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
    if (h == NULL || b == NULL || lef == NULL)
        return;

    struct params_t *p = params_cria(h, b, NULL);

    if (p == NULL)
        return;

    int tpb = 15 + (h->pac * aleat(1, 20));

    fprio_insere(lef, p, EV_SAI, t + tpb);
}

void sai(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef,
         struct mundo_t *w)
{
    if (h == NULL || b == NULL || lef == NULL || w == NULL)
        return;

    cjto_retira(b->pres, h->id);

    struct params_t *pv = params_cria(h, w->bases[aleat(0, N_BASES - 1)], NULL);
    struct params_t *pa = params_cria(NULL, b, NULL);

    if (pv == NULL || pa == NULL) {
        params_destroi(&pv);
        params_destroi(&pa);
        return;
    }

    fprio_insere(lef, pv, EV_VIAJA, t);
    fprio_insere(lef, pa, EV_AVISA, t);
}

void viaja(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef,
           struct mundo_t *w)
{
    if (h == NULL || b == NULL || lef == NULL || w == NULL)
        return;

    struct params_t *p = params_cria(h, b, NULL);

    if (p == NULL)
        return;

    int ds = ponto_distancia(w->bases[h->base], b);
    int dt = ds / h->vel;

    fprio_insere(lef, p, EV_CHEGA, t + dt);
}

void morre(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
}

void missao(int t, struct missao_t *m, struct fprio_t *lef)
{
}

void fim(int t)
{
}
