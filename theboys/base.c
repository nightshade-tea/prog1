#include <stdlib.h>
#include <stdio.h>
#include "conjunto.h"
#include "common.h"
#include "ponto.h"
#include "mundo.h"
#include "fila.h"
#include "base.h"

void base_destroi(struct base_t **b)
{
    if (b == NULL || *b == NULL)
        return;

    (*b)->pres = cjto_destroi((*b)->pres);
    fila_destroi(&((*b)->esp));
    ponto_destroi(&((*b)->loc));

    free(*b);
    *b = NULL;
}

struct base_t *base_cria(int id)
{
    struct base_t *b = malloc(sizeof(struct base_t));

    if (b == NULL)
        return NULL;

    b->loc = ponto_cria(aleat(0, N_TAMANHO_MUNDO - 1),
                        aleat(0, N_TAMANHO_MUNDO - 1));

    b->lot = aleat(B_MIN_LOTACAO, B_MAX_LOTACAO);
    b->pres = cjto_cria(N_HEROIS);
    b->esp = fila_cria();
    b->id = id;
    b->fmax = 0;
    b->mcumpr = 0;

    if (b->loc == NULL || b->esp == NULL || b->pres == NULL) {
        base_destroi(&b);
        return NULL;
    }

    return b;
}

int base_id(struct base_t *b)
{
    if (b == NULL)
        return -1;

    return b->id;
}

int base_lotacao(struct base_t *b)
{
    if (b == NULL)
        return -1;

    return b->lot;
}

struct cjto_t *base_presentes(struct base_t *b)
{
    if (b == NULL)
        return NULL;

    return b->pres;
}

struct fila_t *base_espera(struct base_t *b)
{
    if (b == NULL)
        return NULL;

    return b->esp;
}

struct ponto_t *base_local(struct base_t *b)
{
    if (b == NULL)
        return NULL;

    return b->loc;
}

int base_fila_max(struct base_t *b)
{
    if (b == NULL)
        return -1;

    return b->fmax;
}

int base_missoes_cumpridas(struct base_t *b)
{
    if (b == NULL)
        return -1;

    return b->mcumpr;
}

int base_missoes_cumpridas_inc(struct base_t *b)
{
    if (b == NULL)
        return -1;

    return ++(b->mcumpr);
}

int base_fila_max_atualiza(struct base_t *b)
{
    if (b == NULL)
        return -1;

    if (fila_tamanho(b->esp) > b->fmax)
        return b->fmax = fila_tamanho(b->esp);

    return b->fmax;
}

int base_lotada(struct base_t *b)
{
    if (b == NULL)
        return -1;

    return (cjto_card(b->pres) >= b->lot);
}

// TODO
void base_imprime(struct base_t *b)
{
    if (b == NULL)
        return;

    printf("BASE %2d ", b->id);
    printf("LOT %2d ", b->lot);
    printf("FILA MAX %2d ", b->fmax);
    printf("MISSOES %d\n", b->mcumpr);
}
