// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

#include "fprio.h"
#include <stdlib.h>

/* Libera a memória alocada para o nodo especificado e aterra seu ponteiro. */
void fpnodo_destroi(struct fpnodo_t **nodo)
{
    if (nodo == NULL || *nodo == NULL)
        return;

    free(*nodo);
    *nodo = NULL;
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

    // desaloca todos os nodos da fila
    while (aux != NULL) {
        f->prim = aux->prox;
        fpnodo_destroi(&aux);
        aux = f->prim;
    }

    // desaloca a fila
    free(f);

    return NULL;
}
