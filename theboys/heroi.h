#ifndef HEROI
#define HEROI

#include "conjunto.h"

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
    int base;
};

struct heroi_t *heroi_cria(int id, int base);

void heroi_destroi(struct heroi_t **h);

#endif
