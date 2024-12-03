#ifndef FILA
#define FILA

/* Descreve um nodo da fila. */
struct fnodo_t {
    void *item;             // item associado ao nodo
    int id;                 // id do item
    struct fnodo_t *prox;   // próximo nodo
};

/* Descreve uma fila. */
struct fila_t {
    struct fnodo_t *prim;   // primeiro nodo da fila
    struct fnodo_t *ult;    // último nodo da fila
    int num;                // número de itens na fila
};

/* Cria uma fila vazia.
 * Retorno: ponteiro p/ a fila criada ou NULL em erro. */
struct fila_t *fila_cria();

/* Destroi a fila e todos os seus nodos. NÃO desaloca os itens dos nodos (isso
 * evita com que ocorra um double free quando o mundo for destruído). */
void fila_destroi(struct fila_t **f);

/* Insere o item na fila com o id especificado.
 * Retorno: número de itens na fila após a operação ou -1 em erro. */
int fila_insere(struct fila_t *f, void *item, int id);

/* Retira o primeiro item da fila e o devolve. O id do item é devolvido no
 * parâmetro "id".
 * Retorno: ponteiro p/ o item retirado ou NULL em erro. */
void *fila_retira(struct fila_t *f, int *id);

/* Informa o número de itens na fila.
 * Retorno: num >= 0 ou -1 em erro. */
int fila_tamanho(struct fila_t *f);

/* Imprime o conteúdo da fila no formato "id id id ...", sem espaços no início
 * e no fim, e sem newline. */
void fila_imprime(struct fila_t *f);

#endif
