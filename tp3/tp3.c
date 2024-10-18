#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

#define MAX_TAM 100

/* Lê um número racional da entrada padrão, cria e retorna seu endereço. */
struct racional *ler_r()
{
    struct racional *r;
    long num, den;

    scanf("%ld %ld", &num, &den);
    r = cria_r(num, den);

    if (r == NULL) {
        fprintf(stderr, "FALHA NA ALOCAÇÃO EM ler_r()\n");
        exit(1);
    }

    return r;
}

/* Cria um vetor de ponteiros para racional e retorna seu endereço. */
struct racional **cria_vr(int tam)
{
    struct racional **v;
    v = malloc(tam * sizeof(struct racional *));

    if (v == NULL) {
        fprintf(stderr, "FALHA NA ALOCAÇÃO EM cria_vr()\n");
        exit(1);
    }

    return v;
}

/* Libera a memória alocada para os elementos de um vetor de ponteiros para
 * racional. */
void destroi_vr(struct racional **v, int tam)
{
    int i;
    for (i = 0; i < tam; i++) {
        destroi_r(v[i]);
        v[i] = NULL;
    }
}

/* Preenche um vetor de ponteiros para racional lendo valores da entrada
 * padrão. */
void ler_vr(struct racional *v[], int tam)
{
    int i;
    for (i = 0; i < tam; i++)
        v[i] = ler_r();
}

/* Imprime o conteúdo de um vetor de ponteiros para racional. */
void imprime_vr(struct racional *v[], int tam)
{
    printf("VETOR =");

    int i;
    for (i = 0; i < tam; i++) {
        printf(" ");
        imprime_r(v[i]);
    }

    printf("\n");
}

/* Remove os elementos inválidos do vetor e retorna seu novo tamanho. */
int valida_vr(struct racional *v[], int tam)
{
    int i, novo_tam;
    novo_tam = 0;

    for (i = 0; i < tam; i++) {
        if (valido_r(v[i])) {
            v[novo_tam] = v[i];
            novo_tam++;
        } else {
            destroi_r(v[i]);
            v[i] = NULL;
        }
    }

    return novo_tam;
}

/* Troca dois ponteiros de número racional de posição. */
void troca_r(struct racional **a, struct racional **b)
{
    struct racional *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Ordena um vetor de ponteiros para número racional em ordem crescente
 * (bubble sort). */
void ordena_vr(struct racional *v[], int tam)
{
    if (tam == 1)
        return;

    int i, t;
    t = 0;

    for (i = 0; i < tam - 1; i++) {
        if (compara_r(v[i], v[i + 1]) == 1) {
            troca_r(&v[i], &v[i + 1]);
            t++;
        }
    }

    if (t == 0)
        return;

    ordena_vr(v, tam - 1);
}

/* Soma os elementos de um vetor de ponteiros para racional e retorna o
 * endereço do racional que contém o resultado. */
struct racional *soma_vr(struct racional *v[], int tam)
{
    struct racional *soma;
    struct racional tmp;

    soma = cria_r(0, 1);

    if (soma == NULL) {
        fprintf(stderr, "FALHA NA ALOCAÇÃO EM soma_vr()\n");
        exit(1);
    }

    int i;
    for (i = 0; i < tam; i++) {
        soma_r(v[i], soma, &tmp);
        *soma = tmp;
    }

    return soma;
}

/* Imprime o resultado da soma dos elementos de um vetor de ponteiros para
 * racional. */
void imprime_soma_vr(struct racional *v[], int tam)
{
    struct racional *soma = soma_vr(v, tam);

    printf("SOMA = ");
    imprime_r(soma);
    printf("\n");

    destroi_r(soma);
}

int main()
{
    struct racional **vetor;
    int n;

    scanf("%d", &n);

    if (n <= 0 || n >= MAX_TAM) {
        fprintf(stderr, "VALOR INVALIDO\n");
        return 1;
    }

    vetor = cria_vr(n);

    ler_vr(vetor, n);
    imprime_vr(vetor, n);

    n = valida_vr(vetor, n);
    imprime_vr(vetor, n);

    ordena_vr(vetor, n);
    imprime_vr(vetor, n);

    imprime_soma_vr(vetor, n);

    destroi_vr(vetor, n);
    imprime_vr(vetor, n);

    free(vetor);
    vetor = NULL;

    return 0;
}
