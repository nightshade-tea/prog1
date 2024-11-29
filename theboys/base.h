#ifndef BASE
#define BASE

#include "conjunto.h"
#include "ponto.h"
#include "fila.h"

#define B_MIN_LOTACAO 3
#define B_MAX_LOTACAO 10

struct base_t {
    int id;
    int lot;
    struct cjto_t *pres;
    struct fila_t *esp;
    struct ponto_t *loc;
    int fmax;
    int mcumpr;
};

struct base_t *base_cria(int id);

void base_destroi(struct base_t **b);

int base_id(struct base_t *b);

int base_lotacao(struct base_t *b);

struct cjto_t *base_presentes(struct base_t *b);

struct fila_t *base_espera(struct base_t *b);

struct ponto_t *base_local(struct base_t *b);

int base_fila_max(struct base_t *b);

int base_missoes_cumpridas(struct base_t *b);

int base_missoes_cumpridas_inc(struct base_t *b);

int base_fila_max_atualiza(struct base_t *b);

int base_lotada(struct base_t *b);

void base_imprime(struct base_t *b);

#endif
