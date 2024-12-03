#ifndef PONTO
#define PONTO

struct ponto_t {
    int x;  // coordenada x do ponto
    int y;  // coordenada y do ponto
};

/* Cria um ponto com as coordenadas especificadas.
 * Retorno: endereço do novo ponto ou NULL em caso de erro. */
struct ponto_t *ponto_cria(int x, int y);

/* Destroi um ponto e aterra seu ponteiro. */
void ponto_destroi(struct ponto_t **p);

/* Calcula a distância cartesiana entre dois pontos.
 * Retorno: distância entre os pontos ou -1 em caso de erro. */
int ponto_distancia(struct ponto_t *p, struct ponto_t *q);

#endif
