#ifndef EVENTOS
#define EVENTOS

#include "missao.h"
#include "mundo.h"
#include "fprio.h"
#include "heroi.h"
#include "base.h"

#define EV_CHEGA 0
#define EV_ESPERA 1
#define EV_DESISTE 2
#define EV_AVISA 3
#define EV_ENTRA 4
#define EV_SAI 5
#define EV_VIAJA 6
#define EV_MORRE 7
#define EV_MISSAO 8
#define EV_FIM 9

struct params_t {
    struct heroi_t *h;
    struct base_t *b;
    struct missao_t *m;
};

/* params_t */
struct params_t *params_cria(struct heroi_t *h, struct base_t *b,
                             struct missao_t *m);

void params_destroi(struct params_t **p);

struct heroi_t *params_heroi(struct params_t *p);

struct base_t *params_base(struct params_t *p);

struct missao_t *params_missao(struct params_t *p);

/* eventos */
int chega(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef);

int espera(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef);

int desiste(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef,
            struct mundo_t *w);

int avisa(int t, struct base_t *b, struct fprio_t *lef);

int entra(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef);

int sai(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef,
        struct mundo_t *w);

int viaja(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef);

int morre(int t, struct heroi_t *h, struct base_t *b, struct missao_t *m,
          struct fprio_t *lef);

int missao(int t, struct missao_t *m, struct fprio_t *lef, struct mundo_t *w);

int fim(int t, struct mundo_t *w);

#endif
