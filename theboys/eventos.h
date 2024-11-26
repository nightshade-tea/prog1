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

void chega(struct fprio_t *lef, struct heroi_t *h, struct base_t *b);
void espera(struct fprio_t *lef, struct heroi_t *h, struct base_t *b);
void desiste(struct fprio_t *lef, struct heroi_t *h, struct base_t *b);
void avisa(struct fprio_t *lef, struct base_t *b);
void entra(struct fprio_t *lef, struct heroi_t *h, struct base_t *b);
void sai(struct fprio_t *lef, struct heroi_t *h, struct base_t *b);
void viaja(struct fprio_t *lef, struct heroi_t *h, struct base_t *b);
void morre(struct fprio_t *lef, struct heroi_t *h, struct base_t *b);
void missao(struct fprio_t *lef, struct missao_t *m);
void fim();

#endif
