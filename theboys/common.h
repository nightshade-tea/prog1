#ifndef COMMON
#define COMMON

#include "missao.h"
#include "heroi.h"
#include "base.h"

struct params_t {
    struct heroi_t *h;
    struct base_t *b;
    struct missao_t *m;
};

struct params_t *params_cria(struct heroi_t *h, struct base_t *b,
                             struct missao_t *m);

void params_destroi(struct params_t **p);
int aleat(int min, int max);
void erro(const char *msg);

#endif
