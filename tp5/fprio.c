// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

#include <stdlib.h>
#include <stdio.h>
#include "fprio.h"

/* Cria um nodo com o item, tipo, prioridade e próximo especificados nos
 * parâmetros.
 * Retorno: ponteiro p/ o novo nodo ou NULL em caso de erro. */
struct fpnodo_t *fpnodo_cria(void *item, int tipo, int prio,
                             struct fpnodo_t *prox)
{
    struct fpnodo_t *nodo = malloc(sizeof(struct fpnodo_t));

    if (nodo == NULL)
        return NULL;

    nodo->item = item;
    nodo->tipo = tipo;
    nodo->prio = prio;
    nodo->prox = prox;

    return nodo;
}

/* Libera a memória alocada para o nodo especificado e aterra seu ponteiro.
 * NÃO desaloca o item do nodo. */
void fpnodo_destroi(struct fpnodo_t **nodo)
{
    if (nodo == NULL || *nodo == NULL)
        return;

    free(*nodo);
    *nodo = NULL;
}

/* Libera a memória alocada para o item do nodo e aterra seu ponteiro. */
void fpnodo_destroi_item(struct fpnodo_t *nodo)
{
    if (nodo == NULL || nodo->item == NULL)
        return;

    free(nodo->item);
    nodo->item = NULL;
}

/* Imprime o tipo e a prioridade do nodo no formato "(tipo prio)", sem quebra
 * de linha. */
void fpnodo_imprime(struct fpnodo_t *nodo)
{
    if (nodo == NULL)
        return;

    printf("(%d %d)", nodo->tipo, nodo->prio);
}

/* Verifica se a fila especificada no parâmetro está vazia.
 * Retorno: 1 se a fila estiver vazia, 0 se não estiver vazia, ou -1 em caso de
 * erro. */
int fprio_vazia(struct fprio_t *f)
{
    if (f == NULL)
        return -1;

    return (f->num == 0);
}

/* Verifica se o item já existe em algum nodo da fila.
 * Retorno: 1 se o item já está na fila, 0 se o item não está na fila, ou -1 em
 * caso de erro. */
int fprio_item_incluso(struct fprio_t *f, void *item)
{
    if (f == NULL || item == NULL)
        return -1;

    struct fpnodo_t *aux = f->prim;

    while (aux != NULL) {
        if (aux->item == item)
            return 1;

        aux = aux->prox;
    }

    return 0;
}

struct fprio_t *fprio_cria()
{
    struct fprio_t *f = malloc(sizeof(struct fprio_t));

    if (f == NULL)
        return NULL;

    f->prim = NULL;
    f->num = 0;

    return f;
}

struct fprio_t *fprio_destroi(struct fprio_t *f)
{
    if (f == NULL)
        return NULL;

    struct fpnodo_t *aux = f->prim;

    while (aux != NULL) {
        f->prim = aux->prox;

        fpnodo_destroi_item(aux);
        fpnodo_destroi(&aux);

        aux = f->prim;
    }

    free(f);

    return NULL;
}

int fprio_insere(struct fprio_t *f, void *item, int tipo, int prio)
{
    if (f == NULL || item == NULL || fprio_item_incluso(f, item))
        return -1;

    struct fpnodo_t *novo = fpnodo_cria(item, tipo, prio, NULL);

    if (novo == NULL)
        return -1;

    // inserir em uma fila vazia
    if (fprio_vazia(f)) {
        f->prim = novo;
        return ++(f->num);
    }

    struct fpnodo_t *pivot = f->prim;

    if (pivot == NULL) {
        fpnodo_destroi(&novo);
        return -1;
    }

    // inserir no início
    if (novo->prio < pivot->prio) {
        f->prim = novo;
        novo->prox = pivot;
        return ++(f->num);
    }

    // caso geral
    while (pivot->prox != NULL && novo->prio >= pivot->prox->prio)
        pivot = pivot->prox;

    novo->prox = pivot->prox;
    pivot->prox = novo;

    return ++(f->num);
}

void *fprio_retira(struct fprio_t *f, int *tipo, int *prio)
{
    if (f == NULL || tipo == NULL || prio == NULL || fprio_vazia(f))
        return NULL;

    struct fpnodo_t *aux = f->prim;

    if (aux == NULL)
        return NULL;

    *tipo = aux->tipo;
    *prio = aux->prio;
    void *item = aux->item;

    f->prim = aux->prox;
    f->num--;

    fpnodo_destroi(&aux);

    return item;
}

int fprio_tamanho(struct fprio_t *f)
{
    if (f == NULL)
        return -1;

    return f->num;
}

void fprio_imprime(struct fprio_t *f)
{
    if (f == NULL || fprio_vazia(f))
        return;

    struct fpnodo_t *aux = f->prim;

    if (aux == NULL)
        return;

    fpnodo_imprime(aux);
    aux = aux->prox;

    while (aux != NULL) {
        printf(" ");
        fpnodo_imprime(aux);
        aux = aux->prox;
    }
}
