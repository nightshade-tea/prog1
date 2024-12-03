#ifndef MISSAO
#define MISSAO

#include "conjunto.h"
#include "ponto.h"

/* Valores mínimo e máximo usados para sortear o atributo de perigo e a
 * quantidade de habilidades da base. */
#define M_MIN_HABILIDADES 6
#define M_MAX_HABILIDADES 10

#define M_MIN_PERIGO 0
#define M_MAX_PERIGO 100

struct missao_t {
    int id;                 // id único identificador
    struct cjto_t *habs;    // conjunto de habilidades necessárias p/ cumprir
    int per;                // perigo da missão
    struct ponto_t *loc;    // local da missão no plano
    int cumpr;              // indica se a missão foi cumprida
    int tents;              // número de tentativas
};

/* Cria uma missao com o id especificado. As outras propriedades são escolhidas
 * aleatoriamente.
 * Retorno: ponteiro p/ a nova missao ou NULL em caso de erro. */
struct missao_t *missao_cria(int id);

/* Libera a memória alocada para a missao e todos os seus atributos */
void missao_destroi(struct missao_t **m);

/* Devolve o valor do atributo id da missao.
 * Retorno: valor de id ou -1 em caso de erro. */
int missao_id(struct missao_t *m);

/* Devolve o endereço do conjunto de habilidades da missao.
 * Retorno: valor de habs ou NULL em caso de erro. */
struct cjto_t *missao_habilidades(struct missao_t *m);

/* Devolve o valor do atributo per (perigo) da missao.
 * Retorno: valor de per ou -1 em caso de erro. */
int missao_perigo(struct missao_t *m);

/* Devolve o endereço do local da missao.
 * Retorno: valor de loc ou NULL em caso de erro, */
struct ponto_t *missao_local(struct missao_t *m);

/* Verifica se a missao já foi cumprida.
 * Retorno: 1 se a missao foi cumprida, 0 se a missao não foi cumprida, ou -1
 * em caso de erro. */
int missao_cumprida(struct missao_t *m);

/* Devolve o número de tentativas da missão.
 * Retorno: valor de tents ou -1 em caso de erro. */
int missao_tentativas(struct missao_t *m);

/* Incrementa o número de tentativas da missao.
 * Retorno: valor de tents após a operação ou -1 em caso de erro. */
int missao_tenta(struct missao_t *m);

/* Marca a missao como cumprida. */
void missao_cumpre(struct missao_t *m);

#endif
