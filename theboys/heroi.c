#include <stdlib.h>
#include <stdio.h>
#include "conjunto.h"
#include "common.h"
#include "mundo.h"
#include "heroi.h"
#include "base.h"

void heroi_destroi(struct heroi_t **h)
{
    if (h == NULL || *h == NULL)
        return;

    (*h)->habs = cjto_destroi((*h)->habs);

    free(*h);
    *h = NULL;
}

struct heroi_t *heroi_cria(int id, struct base_t *b)
{
    struct heroi_t *h = malloc(sizeof(struct heroi_t));

    if (h == NULL)
        return NULL;

    h->habs =
        cjto_aleat(aleat(H_MIN_HABILIDADES, H_MAX_HABILIDADES), N_HABILIDADES);

    if (h->habs == NULL) {
        heroi_destroi(&h);
        return NULL;
    }

    h->id = id;
    h->base = b;
    h->exp = H_EXPERIENCIA_INICIAL;
    h->pac = aleat(H_MIN_PACIENCIA, H_MAX_PACIENCIA);
    h->vel = aleat(H_MIN_VELOCIDADE, H_MAX_VELOCIDADE);
    h->morto = 0;

    return h;
}

int heroi_id(struct heroi_t *h)
{
    if (h == NULL)
        return -1;

    return h->id;
}

struct cjto_t *heroi_habilidades(struct heroi_t *h)
{
    if (h == NULL)
        return NULL;

    return h->habs;
}

int heroi_paciencia(struct heroi_t *h)
{
    if (h == NULL)
        return -1;

    return h->pac;
}

int heroi_velocidade(struct heroi_t *h)
{
    if (h == NULL)
        return -1;

    return h->vel;
}

int heroi_experiencia(struct heroi_t *h)
{
    if (h == NULL)
        return -1;

    return h->exp;
}

struct base_t *heroi_base(struct heroi_t *h)
{
    if (h == NULL)
        return NULL;

    return h->base;
}

int heroi_morto(struct heroi_t *h)
{
    if (h == NULL)
        return -1;

    return h->morto;
}

void heroi_chega(struct heroi_t *h, struct base_t *b)
{
    if (h == NULL || b == NULL)
        return;

    h->base = b;
}

void heroi_morre(struct heroi_t *h)
{
    if (h == NULL)
        return;

    h->morto = 1;
}

int heroi_experiencia_inc(struct heroi_t *h)
{
    if (h == NULL)
        return -1;

    return ++(h->exp);
}

void heroi_imprime(struct heroi_t *h)
{
    if (h == NULL)
        return;

    printf("HEROI %2d ", h->id);
    printf("%5s ", heroi_morto(h) ? "MORTO" : "VIVO");
    printf("PAC %3d ", h->pac);
    printf("VEL %4d ", h->vel);
    printf("EXP %4d ", h->exp);
    printf("HABS [ ");
    cjto_imprime(h->habs);
    printf(" ]\n");
}
