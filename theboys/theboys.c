#include <stdlib.h>
#include <stdio.h>
#include "eventos.h"
#include "common.h"
#include "missao.h"
#include "mundo.h"
#include "heroi.h"
#include "base.h"
#include "fila.h"

/* Insere os eventos chega() iniciais na LEF. Cada herói chega em uma base
 * aleatória em algum momento dos três primeiros dias de simulação.
 * Retorno: 0 em caso de sucesso ou -1 em caso de erro. */
int agendar_chegadas(struct mundo_t *w, struct fprio_t *lef)
{
    if (lef == NULL || w == NULL)
        return -1;

    int i;
    for (i = 0; i < N_HEROIS; i++) {
        int b = aleat(0, N_BASES - 1);
        int t = aleat(0, 4320); // 4320 = 3 dias

        struct params_t *p =
            params_cria(mundo_heroi(w, i), mundo_base(w, b), NULL);

        if (p == NULL || fprio_insere(lef, p, EV_CHEGA, t) == -1)
            return -1;
    }

    return 0;
}

/* Insere os eventos missao() na LEF. Cada missão é agendada para ocorrer em
 * algum momento da simulação.
 * Retorno: 0 em caso de sucesso ou -1 em caso de erro. */
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

/* Insere o evento fim() na LEF. O evento fim está programado para
 * T_FIM_DO_MUNDO, definido em mundo.h.
 * Retorno: 0 em casode sucesso ou -1 em caso de erro. */
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

    if (w == NULL) {
        erro("FALHA NA ALOCAÇÃO EM mundo_cria()");
        return -1;
    }

    struct fprio_t *lef = fprio_cria();

    if (lef == NULL) {
        erro("FALHA NA ALOCAÇÃO EM fprio_cria()");
        return -1;
    }

    // insere os eventos iniciais na LEF
    if (agendar_chegadas(w, lef)) {
        erro("ERRO EM agendar_chegadas()");
        return -1;
    }

    if (agendar_missoes(w, lef)) {
        erro("ERRO EM agendar_missoes()");
        return -1;
    }

    if (agendar_fim(lef)) {
        erro("ERRO EM agendar_fim()");
        return -1;
    }

    // loop de tratamento de eventos
    int ev;
    int clk;
    int ret;
    do {
        struct params_t *p = fprio_retira(lef, &ev, &clk);

        if (p == NULL)
            erro("FALHA AO RETIRAR EVENTO DA LEF");

        mundo_atualiza_relogio(w, clk);

        switch (ev) {
        case EV_CHEGA:
            ret = chega(mundo_relogio(w), params_heroi(p), params_base(p), lef);
            break;
        case EV_ESPERA:
            ret =
                espera(mundo_relogio(w), params_heroi(p), params_base(p), lef);
            break;
        case EV_DESISTE:
            ret = desiste(mundo_relogio(w), params_heroi(p), params_base(p),
                          lef, w);
            break;
        case EV_AVISA:
            ret = avisa(mundo_relogio(w), params_base(p), lef);
            break;
        case EV_ENTRA:
            ret = entra(mundo_relogio(w), params_heroi(p), params_base(p), lef);
            break;
        case EV_SAI:
            ret =
                sai(mundo_relogio(w), params_heroi(p), params_base(p), lef, w);
            break;
        case EV_VIAJA:
            ret = viaja(mundo_relogio(w), params_heroi(p), params_base(p), lef);
            break;
        case EV_MORRE:
            ret = morre(mundo_relogio(w), params_heroi(p), params_base(p),
                        params_missao(p), lef);
            break;
        case EV_MISSAO:
            ret = missao(mundo_relogio(w), params_missao(p), lef, w);
            break;
        case EV_FIM:
            ret = fim(mundo_relogio(w), w);
            break;
        default:
            erro("EVENTO INVÁLIDO");
        }

        if (ret != 0) {
            switch (ret) {
            case -1:
                fprintf(stderr, "ERRO NO EVENTO %d: ARGUMENTOS INVÁLIDOS\n", ev);
                break;
            case -2:
                fprintf(stderr, "ERRO NO EVENTO %d: FALHA NA ALOCAÇÃO\n", ev);
                break;
            }
        }

        params_destroi(&p);
    } while (ev != EV_FIM);

    // libera a memória alocada para a simulação
    mundo_destroi(&w);
    lef = fprio_destroi(lef);

    return 0;
}
