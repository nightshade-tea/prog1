#ifndef MUNDO
#define MUNDO

#include "missao.h"
#include "heroi.h"
#include "base.h"

/* Tempo de início e tempo de fim da simulação. */
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600

/* Valores de configuração para a simulação (tamanho do mundo, número de
 * habilidades e número de entidades). */
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)

struct mundo_t {
    struct heroi_t **herois;        // vetor de herois
    struct base_t **bases;          // vetor de bases
    struct missao_t **missoes;      // vetor de missoes
    int clk;                        // relogio
    int evs_tratados;               // número de eventos tratados
};

/* Cria o mundo e inicializa seus componentes. */
struct mundo_t *mundo_cria();

/* Libera a memória alocada para o mundo e todos os seus componentes. */
void mundo_destroi(struct mundo_t **w);

/* Devolve o endereço do heroi de id especificado.
 * Retorno: endereço do heroi ou NULL em caso de erro. */
struct heroi_t *mundo_heroi(struct mundo_t *w, int id);

/* Devolve o endereço da base de id especificado.
 * Retorno: endereço da base ou NULL em caso de erro. */
struct base_t *mundo_base(struct mundo_t *w, int id);

/* Devolve o endereço da missao de id especificado.
 * Retorno: endereço da missao ou NULL em caso de erro. */
struct missao_t *mundo_missao(struct mundo_t *w, int id);

/* Devolve o valor de clk (relogio).
 * Retorno: valor de clk ou -1 em caso de erro. */
int mundo_relogio(struct mundo_t *w);

/* Devolve o valor de evs_tratados (número de eventos tratados).
 * Retorno: valor de evs_tratados ou -1 em caso de erro. */
int mundo_eventos_tratados(struct mundo_t *w);

/* Atualiza o relogio para o tempo t. */
void mundo_atualiza_relogio(struct mundo_t *w, int t);

#endif
