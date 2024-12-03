#ifndef HEROI
#define HEROI

#include "conjunto.h"
#include "base.h"

/* Valores mínimo e máximo usados para sortear os atributos de paciência,
 * velocidade e quantidade de habilidades do herói. */
#define H_MIN_PACIENCIA 0
#define H_MAX_PACIENCIA 100

#define H_MIN_VELOCIDADE 50
#define H_MAX_VELOCIDADE 5000

#define H_MIN_HABILIDADES 1
#define H_MAX_HABILIDADES 3

/* Valor inicial para a experiência do herói. */
#define H_EXPERIENCIA_INICIAL 0

struct heroi_t {
    int id;                 // id único identificador
    struct cjto_t *habs;    // conjunto de habilidades
    int pac;                // paciência do herói
    int vel;                // velocidade do herói
    int exp;                // experiência do herói
    struct base_t *base;    // base atual
    int morto;              // indica se o herói está morto
};

/* Cria um heroi com o id e a base especificados. As outras propriedades são
 * escolhidas aleatoriamente.
 * Retorno: ponteiro p/ a nova base ou NULL em caso de erro. */
struct heroi_t *heroi_cria(int id, struct base_t *b);

/* Libera a memória alocada para o herói e todos os seus atributos. */
void heroi_destroi(struct heroi_t **h);

/* Devolve o valor do atributo id do heroi.
 * Retorno: valor de id ou -1 em caso de erro. */
int heroi_id(struct heroi_t *h);

/* Devolve o endereço do conjunto de habilidades do heroi.
 * Retorno: valor de habs ou NULL em caso de erro. */
struct cjto_t *heroi_habilidades(struct heroi_t *h);

/* Devolve o valor do atributo pac (paciência) do heroi.
 * Retorno: valor de pac ou -1 em caso de erro. */
int heroi_paciencia(struct heroi_t *h);

/* Devolve o valor do atributo vel (velocidade) do heroi.
 * Retorno: valor de vel ou -1 em caso de erro. */
int heroi_velocidade(struct heroi_t *h);

/* Devolve o valor do atributo exp (experiência) do heroi.
 * Retorno: valor de exp ou -1 em caso de erro. */
int heroi_experiencia(struct heroi_t *h);

/* Devolve o endereço da base do heroi.
 * Retorno: valor de base ou NULL em caso de erro. */
struct base_t *heroi_base(struct heroi_t *h);

/* Verifica se o heroi está morto.
 * Retorno: 1 se o heroi está morto, 0 se o heroi esta vivo, ou -1 em caso de
 * erro. */
int heroi_morto(struct heroi_t *h);

/* Atualiza a base atual do heroi. */
void heroi_chega(struct heroi_t *h, struct base_t *b);

/* Atualiza o atributo morto do heroi para 1. */
void heroi_morre(struct heroi_t *h);

/* Incrementa a experiência do heroi.
 * Retorno: o valor de exp após a operação ou -1 em caso de erro. */
int heroi_experiencia_inc(struct heroi_t *h);

/* Imprime os atributos do heroi seguindo o padrão
 * "HEROI %2d VIVO/MORTO  PAC %3d VEL %4d EXP %4d HABS [ %d %d ... ]" */
void heroi_imprime(struct heroi_t *h);

#endif
