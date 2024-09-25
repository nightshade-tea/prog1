#include <stdio.h>
#include <string.h>

#define MAX 1024

struct vetor {
    int data[MAX];
    int length;
};

void inicializar_vetor(struct vetor* pvetor);
void adicionar_elemento(int elem, struct vetor* pvetor);
int ler_elemento(int pos, struct vetor* pvetor);
int tamanho(struct vetor* pvetor);
void escrever_vetor(struct vetor* pvetor);

int main()
{
    struct vetor primos;
    inicializar_vetor(&primos);
    adicionar_elemento(2, &primos);

    int n;
    printf("insira o número de primos para calcular: ");
    scanf("%d", &n);

    if (n > MAX) {
        printf("valor informado excede %d (máximo)\n", MAX);
        return 1;
    }

    int i;
    for (i = 1; tamanho(&primos) < n; i++) {
        int x = ler_elemento(tamanho(&primos)-1, &primos) + i;

        int j;
        for (j = 0; j < tamanho(&primos); j++) {
            if (x % ler_elemento(j, &primos) == 0)
                break;
        }

        if (j == tamanho(&primos)) {
            adicionar_elemento(x, &primos);
            i = 1;
        }
    }

    escrever_vetor(&primos);

    return 0;
}


void inicializar_vetor(struct vetor* pvetor)
{
    memset(pvetor->data, 0, MAX*sizeof(int));
    pvetor->length = 0;
}


void adicionar_elemento(int elem, struct vetor* pvetor)
{
    pvetor->data[pvetor->length] = elem;
    pvetor->length++;
}


int ler_elemento(int pos, struct vetor* pvetor)
{
    return pvetor->data[pos];
}


int tamanho(struct vetor* pvetor)
{
    return pvetor->length;
}


void escrever_vetor(struct vetor* pvetor)
{
    int i;
    for (i = 0; i < tamanho(pvetor); i++) {
        printf("%d ", ler_elemento(i, pvetor));
    }
    printf("\n");
}

