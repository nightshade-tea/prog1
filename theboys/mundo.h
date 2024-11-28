#ifndef MUNDO
#define MUNDO

#include "missao.h"
#include "heroi.h"
#include "base.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600

#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)

struct mundo_t {
    struct heroi_t **herois;
    struct base_t **bases;
    struct missao_t **missoes;
    int clk;
};

struct mundo_t *mundo_cria();

void mundo_destroi(struct mundo_t **w);

struct heroi_t *mundo_heroi(struct mundo_t *w, int id);

struct base_t *mundo_base(struct mundo_t *w, int id);

struct missao_t *mundo_missao(struct mundo_t *w, int id);

int mundo_relogio(struct mundo_t *w);

#endif
