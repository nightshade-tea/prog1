#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

/* Cria um nodo com o item, id e próximo especificados nos parâmetros.
 * Retorno: ponteiro p/ o novo nodo ou NULL em caso de erro. */
struct fnodo_t *fnodo_cria(void *item, int id, struct fnodo_t *prox)
{
    struct fnodo_t *n = malloc(sizeof(struct fnodo_t));

    if (n == NULL)
        return NULL;

    n->item = item;
    n->id = id;
    n->prox = prox;

    return n;
}

/* Libera a memória alocada para o nodo especificado e aterra seu ponteiro.
 * NÃO desaloca o item do nodo. */
void fnodo_destroi(struct fnodo_t **n)
{
    if (n == NULL || *n == NULL)
        return;

    free(*n);
    *n = NULL;
}

/* Imprime o id do nodo no formato "id", sem quebra de linha. */
void fnodo_imprime(struct fnodo_t *n)
{
    if (n == NULL)
        return;

    printf("%d", n->id);
}

/* Verifica se a fila especificada no parâmetro está vazia.
 * Retorno: 1 se a fila estiver vazia, 0 se não estiver vazia, ou -1 en caso de
 * erro. */
int fila_vazia(struct fila_t *f)
{
    if (f == NULL)
        return -1;

    return (f->num == 0);
}

/* Verifica se o item já existe em algum nodo da fila.
 * Retorno: 1 se o item já está na fila, 0 se o item não está na fila, ou -1 em
 * caso de erro. */
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

int fila_insere(struct fila_t *f, void *item, int id)
{
    if (f == NULL || item == NULL || fila_item_incluso(f, item))
        return -1;

    struct fnodo_t *novo = fnodo_cria(item, id, NULL);

    if (novo == NULL)
        return -1;

    if (f->ult != NULL)
        f->ult->prox = novo;

    if (fila_vazia(f))
        f->prim = novo;

    f->ult = novo;

    return ++(f->num);
}

void *fila_retira(struct fila_t *f, int *id)
{
    if (f == NULL || f->prim == NULL)
        return NULL;

    struct fnodo_t *aux = f->prim;

    if (f->ult == aux)
        f->ult = NULL;

    f->prim = aux->prox;
    f->num--;

    void *item = aux->item;

    if (id != NULL)
        *id = aux->id;

    fnodo_destroi(&aux);

    return item;
}

int fila_tamanho(struct fila_t *f)
{
    if (f == NULL)
        return -1;

    return f->num;
}

void fila_imprime(struct fila_t *f)
{
    if (f == NULL || fila_vazia(f))
        return;

    struct fnodo_t *aux = f->prim;

    if (aux == NULL)
        return;

    fnodo_imprime(aux);
    aux = aux->prox;

    while (aux != NULL) {
        printf(" ");
        fnodo_imprime(aux);
        aux = aux->prox;
    }
}
