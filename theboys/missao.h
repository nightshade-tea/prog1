#ifndef MISSAO
#define MISSAO

#include "conjunto.h"

#define M_MIN_HABILIDADES 6
#define M_MAX_HABILIDADES 10

#define M_MIN_PERIGO 0
#define M_MAX_PERIGO 100

struct missao_t {
    int id;
    struct cjto_t *habilidades;
    int perigo;
    struct ponto_t *local;
};

struct missao_t *missao_cria(int id);

void missao_destroi(struct missao_t **missao);

#endif
