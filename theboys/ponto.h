#ifndef PONTO
#define PONTO

struct ponto_t {
    int x;
    int y;
};

struct ponto_t *ponto_cria(int x, int y);

void ponto_destroi(struct ponto_t **p);

int ponto_distancia(struct ponto_t *p, struct ponto_t *q);

#endif
