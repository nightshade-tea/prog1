#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* retorna um número aleatório entre min e max, inclusive. */
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

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r(struct racional r)
{
    if (!valido_r(r))
        return r;

    if (r.den < 0) {
        r.num *= -1;
        r.den *= -1;
    }

    long m = labs(mdc(r.num, r.den));
    r.num /= m;
    r.den /= m;

    return r;
}

struct racional cria_r(long numerador, long denominador)
{
    struct racional r = { numerador, denominador };
    return r;
}

int valido_r(struct racional r)
{
    if (r.den == 0)
        return 0;

    return 1;
}

struct racional sorteia_r(long min, long max)
{
    struct racional r = { aleat(min, max), aleat(min, max) };
    return simplifica_r(r);
}

void imprime_r(struct racional r)
{
    r = simplifica_r(r);

    if (!valido_r(r)) {
        printf("INVALIDO");
        return;
    }
    if (r.num == 0) {
        printf("0");
        return;
    }
    if (r.den == 1) {
        printf("%ld", r.num);
        return;
    }
    if (r.num == r.den) {
        printf("1");
        return;
    }

    printf("%ld/%ld", r.num, r.den);
}

struct racional soma_r(struct racional r1, struct racional r2)
{
    if (!valido_r(r1))
        return r1;
    if (!valido_r(r2))
        return r2;

    r1 = simplifica_r(r1);
    r2 = simplifica_r(r2);

    struct racional r;
    r.den = mmc(r1.den, r2.den);
    r.num = r1.num * (r.den / r1.den);
    r.num += r2.num * (r.den / r2.den);

    return simplifica_r(r);
}

struct racional subtrai_r(struct racional r1, struct racional r2)
{
    r2.num *= -1;
    return soma_r(r1, r2);
}

struct racional multiplica_r(struct racional r1, struct racional r2)
{
    if (!valido_r(r1))
        return r1;
    if (!valido_r(r2))
        return r2;

    r1 = simplifica_r(r1);
    r2 = simplifica_r(r2);

    struct racional r = { r1.num * r2.num, r1.den * r2.den };
    return simplifica_r(r);
}

struct racional divide_r(struct racional r1, struct racional r2)
{
    r2 = (struct racional){ r2.den, r2.num };
    return multiplica_r(r1, r2);
}
