#ifndef HEROI
#define HEROI

#include "conjunto.h"
#include "base.h"

#define H_MIN_PACIENCIA 0
#define H_MAX_PACIENCIA 100

#define H_MIN_VELOCIDADE 50
#define H_MAX_VELOCIDADE 5000

#define H_MIN_HABILIDADES 1
#define H_MAX_HABILIDADES 3

#define H_EXPERIENCIA_INICIAL 0

struct heroi_t {
    int id;
    struct cjto_t *habs;
    int pac;
    int vel;
    int exp;
    struct base_t *base;
    int morto;
};

struct heroi_t *heroi_cria(int id, struct base_t *base);

void heroi_destroi(struct heroi_t **h);

int heroi_id(struct heroi_t *h);

struct cjto_t *heroi_habs(struct heroi_t *h);

int heroi_pac(struct heroi_t *h);

int heroi_vel(struct heroi_t *h);

int heroi_exp(struct heroi_t *h);

struct base_t *heroi_base(struct heroi_t *h);

int heroi_morto(struct heroi_t *h);

void heroi_chega(struct heroi_t *h, struct base_t *b);

void heroi_morre(struct heroi_t *h);

void heroi_imprime(struct heroi_t *h);

#endif
