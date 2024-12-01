#ifndef MISSAO
#define MISSAO

#include "conjunto.h"
#include "ponto.h"

#define M_MIN_HABILIDADES 6
#define M_MAX_HABILIDADES 10

#define M_MIN_PERIGO 0
#define M_MAX_PERIGO 100

struct missao_t {
    int id;
    struct cjto_t *habs;
    int per;
    struct ponto_t *loc;
    int cumpr;
    int tents;
};

struct missao_t *missao_cria(int id);

void missao_destroi(struct missao_t **m);

int missao_id(struct missao_t *m);

struct cjto_t *missao_habilidades(struct missao_t *m);

int missao_perigo(struct missao_t *m);

struct ponto_t *missao_local(struct missao_t *m);

int missao_cumprida(struct missao_t *m);

int missao_tentativas(struct missao_t *m);

int missao_tenta(struct missao_t *m);

void missao_cumpre(struct missao_t *m);

#endif