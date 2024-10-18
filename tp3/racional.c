#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* Retorna um número aleatório entre min e max, inclusive. */
long aleat(long min, long max)
{
    return rand() % (max - min + 1) + min;
}

long mdc(long a, long b)
{
    if (a % b == 0)
        return b;

    return mdc(b, a % b);
}

long mmc(long a, long b)
{
    return (a * b) / mdc(a, b);
}

/* Recebe um ponteiro para racional e o simplifica.
 * Se r for inválido, retorna 0. 
 * Se a operação foi bem sucedida, retorna 1. */
int simplifica_r(struct racional *r)
{
    if (!valido_r(r))
        return 0;

    if (r->den < 0) {
        r->num *= -1;
        r->den *= -1;
    }

    long m = labs(mdc(r->num, r->den));
    r->num /= m;
    r->den /= m;

    return 1;
}

struct racional *cria_r(long numerador, long denominador)
{
    struct racional *r = malloc(sizeof(struct racional));

    if (r == NULL)
        return NULL;

    r->num = numerador;
    r->den = denominador;

    return r;
}

void destroi_r(struct racional *r)
{
    free(r);
}

int valido_r(struct racional *r)
{
    if (r == NULL)
        return 0;
    if (r->den == 0)
        return 0;

    return 1;
}

void imprime_r(struct racional *r)
{
    if (r == NULL) {
        printf("NULL");
        return;
    }

    simplifica_r(r);

    if (!valido_r(r)) {
        printf("NaN");
        return;
    }
    if (r->num == 0) {
        printf("0");
        return;
    }
    if (r->den == 1) {
        printf("%ld", r->num);
        return;
    }

    printf("%ld/%ld", r->num, r->den);
}

int compara_r(struct racional *r1, struct racional *r2)
{
    if (!valido_r(r1) || !valido_r(r2))
        return -2;

    struct racional dif;
    subtrai_r(r1, r2, &dif);

    if (dif.num < 0)
        return -1;
    if (dif.num > 0)
        return 1;

    return 0;
}

int soma_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
    if (!valido_r(r1) || !valido_r(r2) || r3 == NULL)
        return 0;

    // tmp é necessário para que operações como r1 = r1 + r2 (quando r3 é algum
    // dos operandos) executem corretamente.
    struct racional tmp;

    simplifica_r(r1);
    simplifica_r(r2);

    tmp.den = mmc(r1->den, r2->den);
    tmp.num = r1->num * (tmp.den / r1->den);
    tmp.num += r2->num * (tmp.den / r2->den);

    *r3 = tmp;

    simplifica_r(r3);

    return 1;
}

int subtrai_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
    if (!valido_r(r2))
        return 0;

    struct racional op_r2 = { -1 * r2->num, r2->den };

    return soma_r(r1, &op_r2, r3);
}

int multiplica_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
    if (!valido_r(r1) || !valido_r(r2) || r3 == NULL)
        return 0;

    simplifica_r(r1);
    simplifica_r(r2);

    r3->num = r1->num * r2->num;
    r3->den = r1->den * r2->den;

    simplifica_r(r3);

    return 1;
}

int divide_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
    if (!valido_r(r2))
        return 0;

    struct racional inv_r2 = { r2->den, r2->num };

    return multiplica_r(r1, &inv_r2, r3);
}
