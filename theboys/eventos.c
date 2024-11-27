#include <stddef.h>
#include "conjunto.h"
#include "eventos.h"
#include "common.h"
#include "missao.h"
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

void desiste(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
}

void avisa(int t, struct base_t *b, struct fprio_t *lef)
{
}

void entra(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
}

void sai(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
}

void viaja(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
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
