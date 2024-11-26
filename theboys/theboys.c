#include "missao.h"
#include "mundo.h"
#include "heroi.h"
#include "base.h"
#include "fila.h"

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

void chega(struct heroi_t *h, struct base_t *b);
void espera(struct heroi_t *h, struct base_t *b);
void desiste(struct heroi_t *h, struct base_t *b);
void avisa(struct base_t *b);
void entra(struct heroi_t *h, struct base_t *b);
void sai(struct heroi_t *h, struct base_t *b);
void viaja(struct heroi_t *h, struct base_t *b);
void morre(struct heroi_t *h, struct base_t *b);
void missao(struct missao_t *m);
void fim();

int main()
{
    return 0;
}
