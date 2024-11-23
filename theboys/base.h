#ifndef BASE
#define BASE

#include "conjunto.h"
#include "ponto.h"
#include "fila.h"

#define B_MIN_LOTACAO 3
#define B_MAX_LOTACAO 10

struct base_t {
    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct fila_t *espera;
    struct ponto_t *local;
};

struct base_t *base_cria(int id);

void base_destroi(struct base_t **base);

#endif
