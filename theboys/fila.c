#include <stdlib.h>
#include "fila.h"

struct fnodo_t *fnodo_cria(void *item, struct fnodo_t *prox)
{
    struct fnodo_t *nodo = malloc(sizeof(struct fnodo_t));

    if (nodo == NULL)
        return NULL;

    nodo->item = item;
    nodo->prox = prox;

    return nodo;
}

void fnodo_destroi(struct fnodo_t **nodo)
{
    if (nodo == NULL || *nodo == NULL)
        return;

    free(*nodo);
    *nodo = NULL;
}

void fnodo_destroi_item(struct fnodo_t *nodo)
{
    if (nodo == NULL || nodo->item == NULL)
        return;

    free(nodo->item);
    nodo->item = NULL;
}

int fila_vazia(struct fila_t *fila)
{
    if (fila == NULL)
        return -1;

    return (fila->num == 0);
}

int fila_item_incluso(struct fila_t *fila, void *item)
{
    if (fila == NULL || item == NULL)
        return -1;

    struct fnodo_t *aux = fila->prim;

    while (aux != NULL) {
        if (aux->item == item)
            return 1;

        aux = aux->prox;
    }

    return 0;
}

struct fila_t *fila_cria()
{
    struct fila_t *fila = malloc(sizeof(struct fila_t));

    if (fila == NULL)
        return NULL;

    fila->prim = fila->ult = NULL;
    fila->num = 0;

    return fila;
}

void fila_destroi(struct fila_t **fila)
{
    if (fila == NULL || *fila == NULL)
        return;

    struct fnodo_t *aux = (*fila)->prim;

    while (aux != NULL) {
        (*fila)->prim = aux->prox;

        fnodo_destroi_item(aux);
        fnodo_destroi(&aux);

        aux = (*fila)->prim;
    }

    free(*fila);
    *fila = NULL;
}

int fila_insere(struct fila_t *fila, void *item)
{
    if (fila == NULL || item == NULL || fila_item_incluso(fila, item))
        return -1;

    struct fnodo_t *novo = fnodo_cria(item, NULL);

    if (novo == NULL)
        return -1;

    if (fila->ult != NULL)
        fila->ult->prox = novo;

    if (fila_vazia(fila))
        fila->prim = novo;

    fila->ult = novo;

    return ++(fila->num);
}

void *fila_retira(struct fila_t *fila)
{
    if (fila == NULL || fila->prim == NULL)
        return NULL;

    struct fnodo_t *aux = fila->prim;

    if (fila->ult == aux)
        fila->ult = NULL;

    fila->prim = aux->prox;
    fila->num--;

    void *item = aux->item;
    fnodo_destroi(&aux);

    return item;
}

int fila_tamanho(struct fila_t *fila)
{
    if (fila == NULL)
        return -1;

    return fila->num;
}
