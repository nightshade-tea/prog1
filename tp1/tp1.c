/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

void imprime_espaco_r(struct racional r);

int main()
{
    srand(0);

    int n, max;
    scanf("%d %d", &n, &max);

    int i;
    for (i = 1; i <= n; i++) {
        printf("%d:", i);

        struct racional r1 = sorteia_r(-max, max);
        struct racional r2 = sorteia_r(-max, max);

        imprime_espaco_r(r1);
        imprime_espaco_r(r2);

        if (!valido_r(r1) || !valido_r(r2)) {
            printf("NUMERO INVALIDO\n");
            return 1;
        }

        struct racional soma = soma_r(r1, r2);
        struct racional sub = subtrai_r(r1, r2);
        struct racional mult = multiplica_r(r1, r2);
        struct racional div = divide_r(r1, r2);

        if (!valido_r(div)) {
            printf("DIVISAO INVALIDA\n");
            return 1;
        }

        imprime_espaco_r(soma);
        imprime_espaco_r(sub);
        imprime_espaco_r(mult);
        imprime_espaco_r(div);
        printf("\n");
    }

    return 0;
}

void imprime_espaco_r(struct racional r)
{
    printf(" ");
    imprime_r(r);
}
