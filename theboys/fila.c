#include <stdlib.h>
#include "fila.h"

struct fnodo_t *fnodo_cria(void *item, struct fnodo_t *prox)
{
    struct fnodo_t *n = malloc(sizeof(struct fnodo_t));

    if (n == NULL)
        return NULL;

    n->item = item;
    n->prox = prox;

    return n;
}

void fnodo_destroi(struct fnodo_t **n)
{
    if (n == NULL || *n == NULL)
        return;

    free(*n);
    *n = NULL;
}

int fila_vazia(struct fila_t *f)
{
    if (f == NULL)
        return -1;

    return (f->num == 0);
}

int fila_item_incluso(struct fila_t *f, void *item)
{
    if (f == NULL || item == NULL)
        return -1;

    struct fnodo_t *aux = f->prim;

    while (aux != NULL) {
        if (aux->item == item)
            return 1;

        aux = aux->prox;
    }

    return 0;
}

struct fila_t *fila_cria()
{
    struct fila_t *f = malloc(sizeof(struct fila_t));

    if (f == NULL)
        return NULL;

    f->prim = f->ult = NULL;
    f->num = 0;

    return f;
}

void fila_destroi(struct fila_t **f)
{
    if (f == NULL || *f == NULL)
        return;

    struct fnodo_t *aux = (*f)->prim;

    while (aux != NULL) {
        (*f)->prim = aux->prox;

        fnodo_destroi(&aux);

        aux = (*f)->prim;
    }

    free(*f);
    *f = NULL;
}

int fila_insere(struct fila_t *f, void *item)
{
    if (f == NULL || item == NULL || fila_item_incluso(f, item))
        return -1;

    struct fnodo_t *novo = fnodo_cria(item, NULL);

    if (novo == NULL)
        return -1;

    if (f->ult != NULL)
        f->ult->prox = novo;

    if (fila_vazia(f))
        f->prim = novo;

    f->ult = novo;

    return ++(f->num);
}

void *fila_retira(struct fila_t *f)
{
    if (f == NULL || f->prim == NULL)
        return NULL;

    struct fnodo_t *aux = f->prim;

    if (f->ult == aux)
        f->ult = NULL;

    f->prim = aux->prox;
    f->num--;

    void *item = aux->item;
    fnodo_destroi(&aux);

    return item;
}

int fila_tamanho(struct fila_t *f)
{
    if (f == NULL)
        return -1;

    return f->num;
}
