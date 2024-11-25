#ifndef FILA
#define FILA

struct fnodo_t {
    void *item;
    struct fnodo_t *prox;
};

struct fila_t {
    struct fnodo_t *prim;
    struct fnodo_t *ult;
    int num;
};

struct fila_t *fila_cria();

void fila_destroi(struct fila_t **f);

int fila_insere(struct fila_t *f, void *item);

void *fila_retira(struct fila_t *f);

int fila_tamanho(struct fila_t *f);

#endif
