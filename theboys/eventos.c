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
