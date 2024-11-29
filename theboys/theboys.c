#include <stdlib.h>
#include <stdio.h>
#include "eventos.h"
#include "common.h"
#include "missao.h"
#include "mundo.h"
#include "heroi.h"
#include "base.h"
#include "fila.h"

int agendar_chegadas(struct mundo_t *w, struct fprio_t *lef)
{
    if (lef == NULL || w == NULL)
        return -1;

    int i;
    for (i = 0; i < N_HEROIS; i++) {
        int b = aleat(0, N_BASES - 1);
        int t = aleat(0, 4320); // 4320 = 3 dias

        struct params_t *p = params_cria(mundo_heroi(w, i), mundo_base(w, b),
                                         NULL);

        if (p == NULL || fprio_insere(lef, p, EV_CHEGA, t) == -1)
            return -1;
    }

    return 0;
}

int agendar_missoes(struct mundo_t *w, struct fprio_t *lef)
{
    if (lef == NULL || w == NULL)
        return -1;

    int i;
    for (i = 0; i < N_MISSOES; i++) {
        int t = aleat(0, T_FIM_DO_MUNDO);

        struct params_t *p = params_cria(NULL, NULL, mundo_missao(w, i));

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
    int clk;
    do {
        struct params_t *p = fprio_retira(lef, &ev, &clk);

        if (p == NULL)
            erro("FALHA AO RETIRAR EVENTO DA LEF");

        mundo_atualiza_relogio(w, clk);

        switch (ev) {
        case EV_CHEGA:
            chega(mundo_relogio(w), params_heroi(p), params_base(p), lef);
            break;
        case EV_ESPERA:
            espera(mundo_relogio(w), params_heroi(p), params_base(p), lef);
            break;
        case EV_DESISTE:
            desiste(mundo_relogio(w), params_heroi(p), params_base(p), lef, w);
            break;
        case EV_AVISA:
            avisa(mundo_relogio(w), params_base(p), lef);
            break;
        case EV_ENTRA:
            entra(mundo_relogio(w), params_heroi(p), params_base(p), lef);
            break;
        case EV_SAI:
            sai(mundo_relogio(w), params_heroi(p), params_base(p), lef, w);
            break;
        case EV_VIAJA:
            viaja(mundo_relogio(w), params_heroi(p), params_base(p), lef);
            break;
        case EV_MORRE:
            morre(mundo_relogio(w), params_heroi(p), params_base(p),
                  params_missao(p), lef);
            break;
        case EV_MISSAO:
            missao(mundo_relogio(w), params_missao(p), lef);
            break;
        case EV_FIM:
            fim(mundo_relogio(w));
            break;
        default:
            erro("EVENTO INVALIDO");
        }

        params_destroi(&p);
    } while (ev != EV_FIM);

    mundo_destroi(&w);
    lef = fprio_destroi(lef);

    return 0;
}
