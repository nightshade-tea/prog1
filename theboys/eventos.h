#ifndef EVENTOS
#define EVENTOS

#include "missao.h"
#include "mundo.h"
#include "fprio.h"
#include "heroi.h"
#include "base.h"

/* Valores usados para identificar unicamente cada evento. */
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

/* struct auxiliar que é inserida na lista de eventos futuros com os argumentos
 * de cada evento. */
struct params_t {
    struct heroi_t *h;  // argumento do tipo heroi_t
    struct base_t *b;   // argumento do tipo base_t
    struct missao_t *m; // argumento do tipo missao_t
};

/* funções para o TAD params_t */

/* Cria uma struct params_t com os argumentos especificados.
 * Retorno: ponteiro para a struct ou NULL em caso de erro. */
struct params_t *params_cria(struct heroi_t *h, struct base_t *b,
                             struct missao_t *m);

/* Libera a memória alocada para uma struct do tipo params_t.
 * NÃO desaloca seus atributos. */
void params_destroi(struct params_t **p);

/* Devolve o endereço do argumento heroi_t.
 * Retorno: valor de h ou NULL em caso de erro. */
struct heroi_t *params_heroi(struct params_t *p);

/* Devolve o endereço do argumento base_t.
 * Retorno: valor de b ou NULL em caso de erro. */
struct base_t *params_base(struct params_t *p);

/* Devolve o endereço do argumento missao_t.
 * Retorno: valor de m ou NULL em caso de erro. */
struct missao_t *params_missao(struct params_t *p);

/* eventos */

/* Os eventos podem receber como parâmetro:
 *   int t: tempo em que o evento ocorre;
 *   struct heroi_t *h: heroi relacionado ao evento;
 *   struct base_t *b: base relacionada ao evento;
 *   struct missao_t *m: missao relacionada ao evento;
 *   struct fprio_t *lef: lista eventos futuros;
 *   struct mundo_t *w: mundo em que o evento ocorre. */

/* Os eventos retornam algum dos valores abaixo:
 *   0: o evento executou com sucesso;
 *  -1: o evento recebeu algum parâmetro inválido;
 *  -2: falha na alocação de memória. */

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
