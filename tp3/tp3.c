#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

#define MAX_TAM 100

/* Cria um vetor de ponteiros para racional e retorna seu endereço.
 * Parâmetros:
 * - tam: tamanho do vetor a ser criado.
 * Retorno:
 * - Endereço do vetor alocado.
 */
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
 * racional.
 * Parâmetros:
 * - v: vetor de ponteiros para racional.
 * - tam: tamanho do vetor.
 */
void destroi_vr(struct racional **v, int tam)
{
    int i;
    for (i = 0; i < tam; i++) {
        destroi_r(v[i]);
        v[i] = NULL;
    }
}

/* Lê um número racional da entrada padrão, cria e retorna seu endereço.
 * Retorno:
 * - Endereço do número racional criado.
 */
struct racional *ler_r()
{
    long num, den;
    scanf("%ld %ld", &num, &den);

    return cria_r(num, den);
}

/* Preenche um vetor de ponteiros para racional lendo valores da entrada padrão.
 * Parâmetros:
 * - v: vetor de ponteiros para racional.
 * - tam: tamanho do vetor.
 */
void ler_vr(struct racional *v[], int tam)
{
    int i;
    for (i = 0; i < tam; i++)
        v[i] = ler_r();
}

/* Imprime o conteúdo de um vetor de ponteiros para racional.
 * Parâmetros:
 * - v: vetor de ponteiros para racional.
 * - tam: tamanho do vetor.
 */
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

/* Remove os elementos inválidos do vetor e retorna seu novo tamanho.
 * Parâmetros:
 * - v: vetor de ponteiros para racional.
 * - tam: tamanho do vetor.
 * Retorno:
 * - Novo tamanho do vetor após a remoção dos elementos inválidos.
 */
int valida_vr(struct racional *v[], int tam)
{
    int i, pos;
    pos = 0;

    for (i = 0; i < tam; i++) {
        if (valido_r(v[i])) {
            v[pos] = v[i];
            pos++;
        } else {
            destroi_r(v[i]);
            v[i] = NULL;
        }
    }

    return pos;
}

/* Troca dois ponteiros de número racional de posição.
 * Parâmetros:
 * - a: ponteiro para o primeiro ponteiro de racional.
 * - b: ponteiro para o segundo ponteiro de racional.
 */
void troca_r(struct racional **a, struct racional **b)
{
    struct racional *tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Ordena um vetor de ponteiros para número racional em ordem crescente.
 * Parâmetros:
 * - v: vetor de ponteiros para racional.
 * - tam: tamanho do vetor.
 */
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

/* Soma os elementos de um vetor de ponteiros para racional e retorna o endereço
 * do racional que contém o resultado.
 * Parâmetros:
 * - v: vetor de ponteiros para racional.
 * - tam: tamanho do vetor.
 * Retorno:
 * - Endereço do número racional que contém a soma dos elementos do vetor.
 */
struct racional *soma_vr(struct racional *v[], int tam)
{
    struct racional *soma = cria_r(0, 1);
    struct racional tmp;

    int i;
    for (i = 0; i < tam; i++) {
        soma_r(v[i], soma, &tmp);
        *soma = tmp;
    }

    return soma;
}

int main()
{
    struct racional **vetor;
    int n;

    scanf("%d", &n);

    if (n <= 0 || n >= MAX_TAM) {
        printf("VALOR INVALIDO\n");
        return 1;
    }

    vetor = cria_vr(n);

    ler_vr(vetor, n);
    imprime_vr(vetor, n);

    n = valida_vr(vetor, n);
    imprime_vr(vetor, n);

    ordena_vr(vetor, n);
    imprime_vr(vetor, n);

    struct racional *soma = soma_vr(vetor, n);
    printf("SOMA = ");
    imprime_r(soma);
    printf("\n");

    destroi_vr(vetor, n);
    imprime_vr(vetor, n);

    free(vetor);
    vetor = NULL;

    destroi_r(soma);
    soma = NULL;

    return 0;
}
