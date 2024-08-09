#include <stdio.h>
#include <stdlib.h>

typedef struct NO no_t;

struct NO{
    int valor;
    int numeroVertices;
    char cor;
    no_t** vizinhos;
};

typedef struct {
    int tamanho;
    no_t** nos;
} lista_t;

int main() {
    //---------Le o grafo---------//
    int tamanho;
    scanf("*Vertices %d ", &tamanho);
    scanf("*Edges ");

    //Inicializa o grafo
    lista_t grafo;
    grafo.tamanho = tamanho;
    grafo.nos = calloc(tamanho, sizeof(no_t*));
    for(int i = 0; i < tamanho; ++i){
        no_t* no = calloc(1, sizeof(no_t));
        no->numeroVertices = 0;
        no->cor = 'b';
        no->valor = i + 1;
        no->vizinhos = malloc(0);
        grafo.nos[i] = no;
    }

    //Le as arestas
    char buffer = fgetc(stdin);
    while(buffer != EOF){
        ungetc(buffer, stdin);
        int vertice_1, vertice_2;
        no_t *no_1, *no_2;
        scanf("%d %d ", &vertice_1, &vertice_2);
        no_1 = grafo.nos[vertice_1 - 1];
        no_2 = grafo.nos[vertice_2 - 1];

        ++no_1->numeroVertices;
        ++no_2->numeroVertices;

        no_1->vizinhos = realloc(no_1->vizinhos, no_1->numeroVertices * sizeof(no_t*));
        no_2->vizinhos = realloc(no_2->vizinhos, no_2->numeroVertices * sizeof(no_t*));

        no_1->vizinhos[no_1->numeroVertices - 1] = no_2;
        no_2->vizinhos[no_2->numeroVertices - 1] = no_1;

        buffer = fgetc(stdin);
    }
    //----------------------------//

    int matriz[grafo.tamanho][grafo.tamanho];
    //Utiliza todos os vértices como raíz
    for(int i = 0; i < grafo.tamanho; ++i){
        //Volta todos os vérices para a cor branca
        for(int j = 0; j < grafo.tamanho; ++j){
            grafo.nos[j]->cor = 'b';
            matriz[i][j] = 2147483647;
        }

        //Escolhe a raiz
        lista_t cinza;
        cinza.tamanho = 1;
        cinza.nos = calloc(1, sizeof(no_t*));
        cinza.nos[0] = grafo.nos[i];

        //Percorre todas as camadas até não ter mais para onde ir
        int distancia = 0;
        while(cinza.tamanho > 0){
            lista_t prox;
            prox.tamanho = 0;
            prox.nos = calloc(0, sizeof(no_t*));

            for(int j = 0; j < cinza.tamanho; ++j){
                matriz[i][cinza.nos[j]->valor - 1] = distancia;

                cinza.nos[j]->cor = 'p';

                for(int k = 0; k < cinza.nos[j]->numeroVertices; ++k){
                    if(cinza.nos[j]->vizinhos[k]->cor == 'b'){
                        cinza.nos[j]->vizinhos[k]->cor = 'c';
                        ++prox.tamanho;
                        prox.nos = realloc(prox.nos, prox.tamanho * sizeof(no_t*));
                        prox.nos[prox.tamanho - 1] = cinza.nos[j]->vizinhos[k];
                    }
                }
            }

            //Altera a lista de nós cinzas
            free(cinza.nos);
            cinza.tamanho = prox.tamanho;
            cinza.nos = prox.nos;
            ++distancia;
        }
    }

    //Imprime a matriz no arquivo de saída
    for(int i = 0; i < grafo.tamanho; ++i) {
        for (int j = 0; j < grafo.tamanho; ++j) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    //Libera a memória do grafo
    for(int i = 0; i < grafo.tamanho; ++i){
        free(grafo.nos[i]->vizinhos);
        free(grafo.nos[i]);
    }
    free(grafo.nos);

    return 0;
}
