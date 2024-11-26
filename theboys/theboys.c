#include <stdlib.h>
#include <stdio.h>
#include "eventos.h"
#include "common.h"
#include "missao.h"
#include "mundo.h"
#include "heroi.h"
#include "base.h"
#include "fila.h"

struct params_t {
    struct heroi_t *h;
    struct base_t *b;
    struct missao_t *m;
};

struct params_t *params_cria(struct heroi_t *h, struct base_t *b,
                             struct missao_t *m)
{
    struct params_t *p = malloc(sizeof(struct params_t));

    if (p == NULL)
        return NULL;

    p->h = h;
    p->b = b;
    p->m = m;

    return p;
}

void params_destroi(struct params_t **p)
{
    if (p == NULL || *p == NULL)
        return;

    free(*p);
    *p = NULL;
}

int agendar_chegadas(struct mundo_t *w, struct fprio_t *lef)
{
    if (lef == NULL || w == NULL || w->herois == NULL || w->bases == NULL)
        return -1;

    int i;
    for (i = 0; i < N_HEROIS; i++) {
        int b = aleat(0, N_BASES - 1);
        int t = aleat(0, 4320); // 4320 = 3 dias

        struct params_t *p = params_cria(w->herois[i], w->bases[b], NULL);

        if (p == NULL || fprio_insere(lef, p, EV_CHEGA, t) == -1)
            return -1;
    }

    return 0;
}

int agendar_missoes(struct mundo_t *w, struct fprio_t *lef)
{
    if (lef == NULL || w == NULL || w->missoes == NULL)
        return -1;

    int i;
    for (i = 0; i < N_MISSOES; i++) {
        int t = aleat(0, T_FIM_DO_MUNDO);

        struct params_t *p = params_cria(NULL, NULL, w->missoes[i]);

        if (p == NULL || fprio_insere(lef, p, EV_MISSAO, t) == -1)
            return -1;
    }

    return 0;
}

int agendar_fim(struct fprio_t *lef)
{
    if (lef == NULL)
        return -1;

    struct params_t *p = params_cria(NULL, NULL, NULL);

    if (p == NULL || fprio_insere(lef, p, EV_FIM, T_FIM_DO_MUNDO) == -1)
        return -1;

    return 0;
}

int main()
{
    srand(0);

    struct mundo_t *w = mundo_cria();

    if (w == NULL)
        erro("FALHA NA ALOCAÇÃO EM mundo_cria()");

    struct fprio_t *lef = fprio_cria();

    if (lef == NULL)
        erro("FALHA NA ALOCAÇÃO EM fprio_cria()");

    if (agendar_chegadas(w, lef) == -1)
        erro("ERRO EM agendar_chegadas()");

    if (agendar_missoes(w, lef) == -1)
        erro("ERRO EM agendar_missoes()");

    if (agendar_fim(lef) == -1)
        erro("ERRO EM agendar_fim()");

    int ev;
    do {
        struct params_t *p = fprio_retira(lef, &ev, &(w->clk));

        if (p == NULL)
            erro("FALHA AO RETIRAR EVENTO DA LEF");

        switch (ev) {
        case EV_CHEGA:
            chega(lef, p->h, p->b);
            break;
        case EV_ESPERA:
            espera(lef, p->h, p->b);
            break;
        case EV_DESISTE:
            desiste(lef, p->h, p->b);
            break;
        case EV_AVISA:
            avisa(lef, p->b);
            break;
        case EV_ENTRA:
            entra(lef, p->h, p->b);
            break;
        case EV_SAI:
            sai(lef, p->h, p->b);
            break;
        case EV_VIAJA:
            viaja(lef, p->h, p->b);
            break;
        case EV_MORRE:
            morre(lef, p->h, p->b);
            break;
        case EV_MISSAO:
            missao(lef, p->m);
            break;
        default:
            erro("EVENTO INVALIDO");
        }
    } while (ev != EV_FIM);

    fim();

    return 0;
}
