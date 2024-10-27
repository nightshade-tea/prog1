// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular

#include "lista.h"

/* Cria um item com valor, ant e prox especificados nos parametros.
 * Retorno: ponteiro p/ o novo item ou NULL em caso de erro. */
struct item_t *item_cria(int valor, struct item_t *ant, struct item_t *prox)
{
    struct item_t *item = malloc(sizeof(struct item_t));

    if (item == NULL)
        return NULL;

    item->valor = valor;
    item->ant = ant;
    item->prox = prox;

    return item;
}

struct lista_t *lista_cria()
{
    struct lista_t *lst = malloc(sizeof(struct lista_t));

    if (lst == NULL)
        return NULL;

    lst->prim = NULL;
    lst->ult = NULL;
    lst->tamanho = 0;

    return lst;
}

struct lista_t *lista_destroi(struct lista_t *lst)
{
    if (lst == NULL)
        return NULL;

    if (lst->tamanho == 0) {
        free(lst);
        return NULL;
    }

    struct item_t *item = lst->prim;
    struct item_t *aux;

    while (item != NULL) {
        aux = item->prox;
        free(item);
        item = aux;
    }
    free(lst);

    return NULL;
}

int lista_insere(struct lista_t *lst, int item, int pos)
{
    if (lst == NULL)
        return -1;

    if (pos < -1)
        return -1;

    struct item_t *novo = item_cria(item, NULL, NULL);

    if (novo == NULL)
        return -1;

    // inserir no inicio
    if (pos == 0) {
        novo->prox = lst->prim;
        lst->prim = novo;

        if (novo->prox != NULL)
            novo->prox->ant = novo;

        return ++(lst->tamanho);
    }

    // inserir no fim
    if (pos == -1 || pos >= tamanho) {
        novo->ant = lst->ult;
        lst->ult = novo;

        if (novo->ant != NULL)
            novo->ant->prox = novo;

        return ++(lst->tamanho);
    }

    if (pos < (lst->tamanho / 2)) {
        novo->ant = lst->prim;

        int i;
        for (i = 0; i < pos - 1; i++) // prim..pos-1
            novo->ant = novo->ant->prox;

        // apos o for, novo->ant aponta para lst[pos-1]

        novo->prox = novo->ant->prox;
        novo->ant->prox = novo;
        novo->prox->ant = novo;
    } else {
        novo->prox = lst->ult;

        int i;
        for (i = lst->tamanho - 1; i > pos; i--) // ult..pos
            novo->prox = novo->prox->ant;

        // apos o for, novo->prox aponta para lst[pos]

        novo->ant = novo->prox->ant;
        novo->ant->prox = novo;
        novo->prox->ant = novo;
    }

    return ++(lst->tamanho);
}
