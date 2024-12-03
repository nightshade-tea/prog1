#ifndef BASE
#define BASE

#include "conjunto.h"
#include "ponto.h"
#include "mundo.h"
#include "fila.h"

/* Valores mínimo e máximo usados para sortear a lotação da base no momento da
 * criação. */
#define B_MIN_LOTACAO 3
#define B_MAX_LOTACAO 10

struct base_t {
    int id;                 // id único identificador
    int lot;                // lotação da base
    struct cjto_t *pres;    // conjunto de presentes
    struct fila_t *esp;     // fila de espera
    struct ponto_t *loc;    // local da base no plano
    int fmax;               // tamanho máximo da fila de espera
    int mcumpr;             // número de missões cumpridas
};

/* base.h e mundo.h formam uma dependência circular por causa da função
 * base_uniao_habilidades(). É necessário declarar o protótipo da struct mundo_t
 * para que base.h possa ser compilada antes de mundo.h */
struct mundo_t;

/* Cria uma base com o id especificado. As outras propriedades são escolhidas
 * aleatoriamente.
 * Retorno: ponteiro p/ a nova base ou NULL em caso de erro. */
struct base_t *base_cria(int id);

/* Libera a memória alocada para base e todos os seus atributos. */
void base_destroi(struct base_t **b);

/* Devolve o valor do atributo id da base.
 * Retorno: valor de id ou -1 em caso de erro. */
int base_id(struct base_t *b);

/* Devolve o valor do atributo lot (lotação) da base.
 * Retorno: valor de lot ou -1 em caso de erro. */
int base_lotacao(struct base_t *b);

/* Devolve o endereço do conjuto de presentes da base.
 * Retorno: valor de pres ou NULL em caso de erro. */
struct cjto_t *base_presentes(struct base_t *b);

/* Devolve o endereço da fila de espera da base.
 * Retorno: valor de esp ou NULL em caso de erro. */
struct fila_t *base_espera(struct base_t *b);

/* Devolve o endereço do local da base.
 * Retorno: valor de loc ou NULL em caso de erro. */
struct ponto_t *base_local(struct base_t *b);

/* Devolve o tamanho máximo da fila de espera.
 * Retorno: valor de fmax ou -1 em caso de erro. */
int base_fila_max(struct base_t *b);

/* Devolve o número de missões cumpridas na base.
 * Retorno: valor de mcumpr ou -1 em caso de erro. */
int base_missoes_cumpridas(struct base_t *b);

/* Incrementa o número de missões cumpridas.
 * Retorno: valor de mcumpr após ser incrementado. */
int base_missoes_cumpridas_inc(struct base_t *b);

/* Atualiza o tamanho máximo da fila de espera.
 * Retorno: valor de fmax após ser atualizado. */
int base_fila_max_atualiza(struct base_t *b);

/* Checa se o número de presentes na base é maior ou igual a lotação.
 * Retorno: 1 se a base está lotada ou 0 se não está lotada. */
int base_lotada(struct base_t *b);

/* Cria um conjunto que é resultado da união das habilidades de todos os heróis
 * presentes na base.
 * Retorno: endereço para o conjunto união ou NULL em caso de erro. */
struct cjto_t *base_uniao_habilidades(struct base_t *b, struct mundo_t *w);

/* Imprime os atributos da base seguindo o padrão
 * "BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n" */
void base_imprime(struct base_t *b);

#endif
