#include <stdlib.h>
#include <stdio.h>
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

// TODO: adicionar valor de retorno (erro) para os eventos
// TODO: fazer funcoes mensagemX_<evento>()

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

struct heroi_t *params_heroi(struct params_t *p)
{
    if (p == NULL)
        return NULL;

    return p->h;
}

struct base_t *params_base(struct params_t *p)
{
    if (p == NULL)
        return NULL;

    return p->b;
}

struct missao_t *params_missao(struct params_t *p)
{
    if (p == NULL)
        return NULL;

    return p->m;
}

void mensagem_chega(int t, struct heroi_t *h, struct base_t *b, int espera)
{
    if (h == NULL || b == NULL)
        return;

    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ", t, heroi_id(h),
           base_id(b), cjto_card(base_presentes(b)), base_lotacao(b));

    if (espera)
        printf("ESPERA\n");
    else
        printf("DESISTE\n");
}

void chega(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
    if (h == NULL || heroi_morto(h) || b == NULL || lef == NULL)
        return;

    heroi_chega(h, b);

    int espera;
    if (!base_lotada(b) && fila_tamanho(base_espera(b)) == 0)
        espera = 1;
    else
        espera = heroi_paciencia(h) > (10 * fila_tamanho(base_espera(b)));

    struct params_t *p = params_cria(h, b, NULL);

    if (p == NULL)
        return;

    if (espera)
        fprio_insere(lef, p, EV_ESPERA, t);
    else
        fprio_insere(lef, p, EV_DESISTE, t);

    mensagem_chega(t, h, b, espera);
}

void espera(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
    if (h == NULL || heroi_morto(h) || b == NULL || lef == NULL)
        return;

    struct params_t *p = params_cria(NULL, b, NULL);

    if (p == NULL)
        return;
    
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", t, heroi_id(h), base_id(b),
           fila_tamanho(base_espera(b)));

    fila_insere(base_espera(b), h, heroi_id(h));

    fprio_insere(lef, p, EV_AVISA, t);
}

void desiste(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef,
             struct mundo_t *w)
{
    if (h == NULL || heroi_morto(h) || b == NULL || lef == NULL || w == NULL)
        return;

    struct params_t *p = params_cria(h, mundo_base(w, aleat(0, N_BASES - 1)),
                                     NULL);

    if (p == NULL)
        return;

    printf("%6d: DESIST HEROI %2d BASE %d\n", t, heroi_id(h), base_id(b));

    fprio_insere(lef, p, EV_VIAJA, t);
}

void avisa(int t, struct base_t *b, struct fprio_t *lef)
{
    if (b == NULL || lef == NULL)
        return;

    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA [ ", t, base_id(b),
           cjto_card(base_presentes(b)), base_lotacao(b));
    fila_imprime(base_espera(b));
    printf(" ]\n");

    while (!base_lotada(b) && fila_tamanho(base_espera(b)) > 0) {
        struct heroi_t *h = fila_retira(base_espera(b), NULL);
        struct params_t *p = params_cria(h, b, NULL);

        if (h != NULL && p != NULL) {
            cjto_insere(base_presentes(b), heroi_id(h));
            fprio_insere(lef, p, EV_ENTRA, t);
            printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", t, base_id(b),
                   heroi_id(h));
        } else {
            params_destroi(&p);
        }
    }

    base_fila_max_atualiza(b);
}

void entra(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
    if (h == NULL || heroi_morto(h) || b == NULL || lef == NULL)
        return;

    struct params_t *p = params_cria(h, b, NULL);

    if (p == NULL)
        return;

    int tpb = 15 + (heroi_paciencia(h) * aleat(1, 20));

    printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n", t, heroi_id(h),
           base_id(b), cjto_card(base_presentes(b)), base_lotacao(b), t + tpb);

    fprio_insere(lef, p, EV_SAI, t + tpb);
}

void sai(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef,
         struct mundo_t *w)
{
    if (h == NULL || heroi_morto(h) || b == NULL || lef == NULL || w == NULL)
        return;

    cjto_retira(base_presentes(b), heroi_id(h));

    struct params_t *pv = params_cria(h, mundo_base(w, aleat(0, N_BASES - 1)),
                                      NULL);

    struct params_t *pa = params_cria(NULL, b, NULL);

    if (pv == NULL || pa == NULL) {
        params_destroi(&pv);
        params_destroi(&pa);
        return;
    }

    printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n", t, heroi_id(h),
           base_id(b), cjto_card(base_presentes(b)), base_lotacao(b));

    fprio_insere(lef, pv, EV_VIAJA, t);
    fprio_insere(lef, pa, EV_AVISA, t);
}

void viaja(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef)
{
    if (h == NULL || heroi_morto(h) || b == NULL || lef == NULL)
        return;

    struct params_t *p = params_cria(h, b, NULL);

    if (p == NULL)
        return;

    int ds = ponto_distancia(base_local(heroi_base(h)), base_local(b));
    int dt = ds / heroi_velocidade(h);

    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", t,
           heroi_id(h), base_id(heroi_base(h)), base_id(b), ds,
           heroi_velocidade(h), t + dt);

    fprio_insere(lef, p, EV_CHEGA, t + dt);
}

void morre(int t, struct heroi_t *h, struct base_t *b, struct missao_t *m,
           struct fprio_t *lef)
{
    if (h == NULL || heroi_morto(h) || b == NULL || lef == NULL)
        return;

    cjto_retira(base_presentes(b), heroi_id(h));
    heroi_morre(h);

    printf("%6d: MORRE  HEROI %2d MISSAO %d\n", t, heroi_id(h), missao_id(m));

    struct params_t *p = params_cria(NULL, b, NULL);

    if (p == NULL)
        return;

    fprio_insere(lef, p, EV_AVISA, t);
}

struct base_t *encontra_bmp(struct missao_t *m, struct mundo_t *w)
{
    if (m == NULL || w == NULL)
        return NULL;

    struct cjto_t *habs_necessarias = missao_habilidades(m);
    struct base_t *bmp = NULL;
    int i;

    for (i = 0; i < N_BASES; i++) {
        struct base_t *b = mundo_base(w, i);
        struct cjto_t *b_habs = base_uniao_habilidades(b, w);

        int dist_atual = ponto_distancia(base_local(bmp), missao_local(m));
        int dist_b = ponto_distancia(base_local(b), missao_local(m));

        int eh_mais_perto = (bmp == NULL || dist_b < dist_atual);
        int tem_habs_necessarias = (cjto_contem(b_habs, habs_necessarias) == 1);

        if (tem_habs_necessarias && eh_mais_perto)
            bmp = b;

        b_habs = cjto_destroi(b_habs);
    }

    return bmp;
}

// TODO: modularizar missao()
void missao(int t, struct missao_t *m, struct fprio_t *lef, struct mundo_t *w)
{
    if (m == NULL || lef == NULL)
        return;

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", t, missao_id(m),
           missao_tentativas(m));
    cjto_imprime(missao_habilidades(m));
    printf(" ]\n");

    missao_tenta(m);

    struct base_t *bmp = encontra_bmp(m, w);

    if (bmp == NULL) { // IMPOSSIVEL
        struct params_t *p = params_cria(NULL, NULL, m);

        if (p == NULL)
            return;

        fprio_insere(lef, p, EV_MISSAO, t + (24 * 60));
        printf("%6d: MISSAO %d IMPOSSIVEL\n", t, missao_id(m));
        return;
    }

    missao_cumpre(m);
    
    struct cjto_t *habs_bmp = base_uniao_habilidades(bmp, w);

    printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", t, missao_id(m),
           base_id(bmp));
    cjto_imprime(habs_bmp);
    printf(" ]\n");

    cjto_destroi(habs_bmp);

    int i;
    for (i = 0; i < N_HEROIS; i++) {
        struct heroi_t *h = mundo_heroi(w, i);

        if (cjto_pertence(base_presentes(bmp), heroi_id(h)) != 1)
            continue;

        int risco = missao_perigo(m);
        risco /= (heroi_paciencia(h) + heroi_experiencia(h) + 1.0);

        if (risco > aleat(0, 30)) {
            struct params_t *p = params_cria(h, bmp, m);
            fprio_insere(lef, p, EV_MORRE, t);
        } else {
            heroi_experiencia_inc(h);
        }
    }
}

void fim(int t)
{
    // TODO

    printf("%6d: FIM\n", t);
}
