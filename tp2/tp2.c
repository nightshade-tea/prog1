#include <stdio.h>
#include "racional.h"

#define MAX_TAM 100

/* Lê um número racional. */
struct racional ler_r()
{
    int num, den;
    scanf("%d %d", &num, &den);

    return cria_r(num, den);
}

/* Lê um vetor de números racionais. */
void ler_vr(struct racional v[], int tam)
{
    int i;
    for (i = 0; i < tam; i++) {
        v[i] = ler_r();
    }
}

/* Imprime um vetor de números racionais. */
void imprime_vr(struct racional v[], int tam)
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
int valida_vr(struct racional v[], int tam)
{
    int i, pos;
    pos = 0;

    for (i = 0; i < tam; i++) {
        if (valido_r(v[i])) {
            v[pos] = v[i];
            pos++;
        }
    }

    return pos;
}

/* Troca dois números racionais de posição. */
void troca_r(struct racional *a, struct racional *b)
{
    struct racional tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Ordena um vetor de números racionais. */
void ordena_vr(struct racional v[], int tam)
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

/* Soma os elementos de um vetor de racionais e retorna o resultado. */
struct racional soma_vr(struct racional v[], int tam)
{
    struct racional soma = cria_r(0, 1);

    int i;
    for (i = 0; i < tam; i++)
        soma_r(v[i], soma, &soma);

    return soma;
}

int main()
{
    struct racional vetor[MAX_TAM];
    int n;

    scanf("%d", &n);

    if (n <= 0 || n >= MAX_TAM) {
        printf("VALOR INVALIDO\n");
        return 1;
    }

    ler_vr(vetor, n);
    imprime_vr(vetor, n);

    n = valida_vr(vetor, n);
    imprime_vr(vetor, n);

    ordena_vr(vetor, n);
    imprime_vr(vetor, n);

    printf("SOMA = ");
    imprime_r(soma_vr(vetor, n));
    printf("\n");

    return 0;
}
