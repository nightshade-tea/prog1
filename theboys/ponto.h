#ifndef PONTO
#define PONTO

struct ponto_t {
    int x;
    int y;
};

struct ponto_t *ponto_cria(int x, int y);

void ponto_destroi(struct ponto_t **ponto);

int ponto_distancia(struct ponto_t A, struct ponto_t B);

#endif
