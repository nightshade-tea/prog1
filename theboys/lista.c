// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular

#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

/* Cria um item com valor, ant e prox especificados nos parâmetros.
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

/* Libera a memória alocada para o item especificado e aterra seu ponteiro. */
void item_destroi(struct item_t **item)
{
    if (item == NULL || *item == NULL)
        return;

    free(*item);
    *item = NULL;
}

/* Verifica se a lista especificada no parâmetro está vazia.
 * Retorno: 1 se a lista estiver vazia, 0 se não estiver vazia, ou -1 caso o
 * ponteiro passado seja nulo. */
int lista_vazia(struct lista_t *lst)
{
    if (lst == NULL)
        return -1;

    return (lst->tamanho == 0);
}

/* Verifica se a posição passada no parâmetro é válida na lista.
 * Uma posição é considerada válida se está entre 0, 1, ..., n (inclusive),
 * onde n é o índice do último elemento.
 * A posição -1 também é válida e representa o último elemento.
 * Retorno: 1 se a posição for válida, 0 se não for válida, ou -1 em caso de
 * erro */
int lista_posicao_valida(struct lista_t *lst, int pos)
{
    if (lst == NULL)
        return -1;

    if (pos < -1 || pos >= lst->tamanho)
        return 0;

    return 1;
}

/* Busca o item na posição especificada no parâmetro. Se a posição for -1,
 * retorna o último item.
 * Retorno: ponteiro p/ o item em caso de sucesso, NULL se não for encontrado
 * ou em caso de erro. */
struct item_t *lista_busca_posicao(struct lista_t *lst, int pos)
{
    if (lst == NULL)
        return NULL;

    if (lista_vazia(lst) || !lista_posicao_valida(lst, pos))
        return NULL;

    if (pos == 0)
        return lst->prim;

    if (pos == -1 || pos == (lst->tamanho - 1))
        return lst->ult;

    struct item_t *aux;

    // aqui escolhemos o caminho mais curto para encontrar o item
    if (pos < (lst->tamanho / 2)) {
        aux = lst->prim;

        if (aux == NULL)
            return NULL;

        int i;
        for (i = 0; i < pos; i++) {
            if (aux->prox == NULL)
                return NULL;

            aux = aux->prox;
        }
    } else {
        aux = lst->ult;

        if (aux == NULL)
            return NULL;

        int i;
        for (i = (lst->tamanho - 1); i > pos; i--) {
            if (aux->ant == NULL)
                return NULL;

            aux = aux->ant;
        }
    }

    return aux;
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

    struct item_t *aux = lst->prim;

    // desaloca todos os itens da lista
    while (aux != NULL) {
        lst->prim = aux->prox;
        item_destroi(&aux);
        aux = lst->prim;
    }

    // desaloca a lista
    free(lst);

    return NULL;
}

int lista_insere(struct lista_t *lst, int item, int pos)
{
    if (lst == NULL || pos < -1)
        return -1;

    struct item_t *novo = item_cria(item, NULL, NULL);

    if (novo == NULL)
        return -1;

    // inserir em uma lista vazia
    if (lista_vazia(lst)) {
        lst->prim = lst->ult = novo;

        return ++(lst->tamanho);
    }

    // inserir no início
    if (pos == 0) {
        if (lst->prim == NULL) {
            item_destroi(&novo);
            return -1;
        }

        novo->prox = lst->prim;
        lst->prim = novo;
        novo->prox->ant = novo;

        return ++(lst->tamanho);
    }

    // inserir no fim
    if (pos == -1 || pos >= lst->tamanho) {
        if (lst->ult == NULL) {
            item_destroi(&novo);
            return -1;
        }

        novo->ant = lst->ult;
        lst->ult = novo;
        novo->ant->prox = novo;

        return ++(lst->tamanho);
    }

    struct item_t *pivot = lista_busca_posicao(lst, pos);

    if (pivot == NULL || pivot->ant == NULL) {
        item_destroi(&novo);
        return -1;
    }

    novo->prox = pivot;
    novo->ant = pivot->ant;

    pivot->ant->prox = novo;
    pivot->ant = novo;

    return ++(lst->tamanho);
}

int lista_retira(struct lista_t *lst, int *item, int pos)
{
    if (lst == NULL || item == NULL)
        return -1;

    if (lista_vazia(lst) || !lista_posicao_valida(lst, pos))
        return -1;

    struct item_t *rmv = lista_busca_posicao(lst, pos);

    if (rmv == NULL)
        return -1;

    *item = rmv->valor;

    // atualizar os ponteiros da lista
    if (rmv->ant != NULL)
        rmv->ant->prox = rmv->prox;
    else
        lst->prim = rmv->prox;

    if (rmv->prox != NULL)
        rmv->prox->ant = rmv->ant;
    else
        lst->ult = rmv->ant;

    item_destroi(&rmv);

    return --(lst->tamanho);
}

int lista_consulta(struct lista_t *lst, int *item, int pos)
{
    if (lst == NULL || item == NULL)
        return -1;

    if (lista_vazia(lst) || !lista_posicao_valida(lst, pos))
        return -1;

    struct item_t *aux = lista_busca_posicao(lst, pos);

    if (aux == NULL)
        return -1;

    *item = aux->valor;

    return lst->tamanho;
}

int lista_procura(struct lista_t *lst, int valor)
{
    if (lst == NULL || lista_vazia(lst))
        return -1;

    struct item_t *aux = lst->prim;
    int pos = 0;

    while (aux != NULL && aux->valor != valor) {
        aux = aux->prox;
        pos++;
    }

    if (aux == NULL)
        return -1;

    return pos;
}

int lista_tamanho(struct lista_t *lst)
{
    if (lst == NULL)
        return -1;

    return lst->tamanho;
}

void lista_imprime(struct lista_t *lst)
{
    if (lst == NULL || lista_vazia(lst))
        return;

    struct item_t *aux = lst->prim;

    if (aux == NULL)
        return;

    printf("%d", aux->valor);
    aux = aux->prox;

    while (aux != NULL) {
        printf(" %d", aux->valor);
        aux = aux->prox;
    }
}
