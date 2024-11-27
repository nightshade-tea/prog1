#ifndef EVENTOS
#define EVENTOS

#include "missao.h"
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

void chega(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef);
void espera(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef);
void desiste(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef,
             struct mundo_t *w);

void avisa(int t, struct base_t *b, struct fprio_t *lef);
void entra(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef);
void sai(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef);
void viaja(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef);
void morre(int t, struct heroi_t *h, struct base_t *b, struct fprio_t *lef);
void missao(int t, struct missao_t *m, struct fprio_t *lef);
void fim(int t);

#endif
