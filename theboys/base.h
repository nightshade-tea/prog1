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
};

struct base_t *base_cria(int id);

void base_destroi(struct base_t **b);

int base_id(struct base_t *b);

int base_lotada(struct base_t *b);

void base_imprime(struct base_t *b);

#endif
