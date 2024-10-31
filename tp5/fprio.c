// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

#include "fprio.h"
#include <stdlib.h>

struct fprio_t *fprio_cria()
{
    struct fprio_t *fila = malloc(sizeof(struct fprio_t));

    if (fila == NULL)
        return NULL;

    fila->prim = NULL;
    fila->num = 0;

    return fila;
}
