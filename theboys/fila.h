#ifndef FILA
#define FILA

struct fnodo_t {
    void *item;
    int id;
    struct fnodo_t *prox;
};

struct fila_t {
    struct fnodo_t *prim;
    struct fnodo_t *ult;
    int num;
};

struct fila_t *fila_cria();

// obs: diferentemente de fprio, fila_destroi NAO desaloca os itens dos nodos.
// isso evita com que ocorra um double free!!
void fila_destroi(struct fila_t **f);

int fila_insere(struct fila_t *f, void *item, int id);

void *fila_retira(struct fila_t *f, int *id);

int fila_tamanho(struct fila_t *f);

void fila_imprime(struct fila_t *f);

#endif
