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
    if (h == NULL || heroi_morto(h) || b == NULL || lef == NULL)
        return;

    heroi_chega(h, b);

    int espera;
    if (!base_lotada(b) && base_tamanho_fila_esp(b) == 0)
        espera = 1;
    else
        espera = heroi_pac(h) > (10 * base_tamanho_fila_esp(b));

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
    if (h == NULL || heroi_morto(h) || b == NULL || lef == NULL)
        return;

    fila_insere(base_espera(b), h);

    struct params_t *p = params_cria(NULL, b, NULL);

    if (p == NULL)
        return;

    fprio_insere(lef, p, EV_AVISA, t);
}

void desiste(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef,
             struct mundo_t *w)
{
    if (h == NULL || heroi_morto(h) || b == NULL || lef == NULL || w == NULL)
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

    while (!base_lotada(b) && base_tamanho_fila_esp(b) > 0) {
        struct heroi_t *h = fila_retira(base_espera(b));
        struct params_t *p = params_cria(h, b, NULL);

        if (h != NULL && p != NULL) {
            cjto_insere(base_presentes(b), heroi_id(h));
            fprio_insere(lef, p, EV_ENTRA, t);
        } else {
            params_destroi(&p);
        }
    }
}

void entra(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
    if (h == NULL || heroi_morto(h) || b == NULL || lef == NULL)
        return;

    struct params_t *p = params_cria(h, b, NULL);

    if (p == NULL)
        return;

    int tpb = 15 + (heroi_pac(h) * aleat(1, 20));

    fprio_insere(lef, p, EV_SAI, t + tpb);
}

void sai(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef,
         struct mundo_t *w)
{
    if (h == NULL || heroi_morto(h) || b == NULL || lef == NULL || w == NULL)
        return;

    cjto_retira(base_presentes(b), heroi_id(h));

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
    if (h == NULL || heroi_morto(h) || heroi_base(h) == NULL || b == NULL ||
        lef == NULL || w == NULL)
        return;

    struct params_t *p = params_cria(h, b, NULL);

    if (p == NULL)
        return;

    int ds = ponto_distancia(base_local(heroi_base(h)), base_local(b));
    int dt = ds / heroi_vel(h);

    fprio_insere(lef, p, EV_CHEGA, t + dt);
}

void morre(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
    if (h == NULL || heroi_morto(h) || b == NULL || lef == NULL)
        return;

    cjto_retira(base_presentes(b), heroi_id(h));
    heroi_morre(h);

    struct params_t *p = params_cria(NULL, b, NULL);

    if (p == NULL)
        return;

    fprio_insere(lef, p, EV_AVISA, t);
}

void missao(int t, struct missao_t *m, struct fprio_t *lef)
{
    if (m == NULL || lef == NULL)
        return;

    // TODO
}

void fim(int t)
{
    // TODO
}
