#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool teste(vector<vector<int>> &grafo, vector<int> &pai, int nVertices, int origem, int destino);

int calcula(vector<vector<int>> &grafo, int nVertices, int origem, int destino);

int main() {
    //Lê o número de vértices do primeiro caso de teste
    int nVertices;
    cin >> nVertices;
    if(nVertices == 0) return 0;

    //Repete até que o número de vértices lido seja 0
    int contador = 1;
    while(true){
        cout << "Network " << contador << '\n';

        //Lê o vértice de origem do fluxo, o de destino e o número de arestas
        int origem, destino, nArestas;
        cin >> origem >> destino >> nArestas;
        --origem;
        --destino;

        //Inicializa os valores das arestas
        vector<vector<int>> grafo(nVertices);
        for(int i = 0; i < nVertices; ++i){
            grafo[i].resize(nVertices, 0);
        }

        //Lê as arestas
        for(int i = 0; i < nArestas; ++i){
            int saida, chegada, tamanho;
            cin >> saida >> chegada >> tamanho;
            --saida;
            --chegada;

            grafo[saida][chegada] += tamanho;
            grafo[chegada][saida] += tamanho;
        }

        //Testa para saber qual o valor máximo
        int maximo = calcula(grafo, nVertices, origem, destino);
        cout << "The bandwidth is " << maximo << ".\n";

        //Lê o número de vértices do próximo caso de teste
        cin >> nVertices;
        if(nVertices == 0){
            break;
        }
        ++contador;
        cout << '\n';
    }
    return 0;
}

bool teste(vector<vector<int>> &grafo, vector<int> &pai, int nVertices, int origem, int destino){
    vector<char> visitado(nVertices, 0);
    queue<int> fila;

    pai[origem] = -1;
    fila.push(origem);

    //Repete até esvaziar a fila
    do{
        int atual = fila.front();
        fila.pop();

        if(!visitado[atual]){
            visitado[atual] = 1;
            for(int i = 0; i < nVertices; ++i){
                if(grafo[atual][i] && !visitado[i]){
                    fila.push(i);
                    pai[i] = atual;
                }
            }
        }
    }while(!fila.empty());

    return visitado[destino];
}

int calcula(vector<vector<int>> &grafo, int nVertices, int origem, int destino){
    vector<int> pai(nVertices);

    //Verifica qual passagem com menor fluxo
    int maximo = 0;
    while(teste(grafo, pai, nVertices, origem, destino)) {
        int menor = 100000;
        for (int chegada = destino; chegada != origem; chegada = pai[chegada]) {
            if(grafo[chegada][pai[chegada]]){
                menor = min(menor, grafo[chegada][pai[chegada]]);
            }
        }

        //Reduz esse fluxo do caminho percorrido
        for (int chegada = destino; chegada != origem; chegada = pai[chegada]) {
            int saida = pai[chegada];
            grafo[saida][chegada] -= menor;
            grafo[chegada][saida] -= menor;
        }
        maximo += menor;
    }
    return maximo;
}