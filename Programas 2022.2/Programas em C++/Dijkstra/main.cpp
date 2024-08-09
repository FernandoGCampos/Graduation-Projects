#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int main() {
    //Lê os números de vértices, arestas e casos de teste
    int nVertices, nArestas, nTestes;
    cin >> nVertices >> nArestas >> nTestes;

    //Lê as arestas
    vector<vector<pair<long long,int>>> grafo(nVertices);
    for(int i = 0; i < nArestas; ++i){
        int origem, destino;
        long long peso;
        cin >> origem >> destino >> peso;

        grafo[--origem].push_back(pair<long long,int> (peso, --destino));
        grafo[destino].push_back(pair<long long,int> (peso, origem));
    }

    //Cria a matriz de distâncias
    vector<vector<long long>> distancias(nVertices);
    for(int i = 0; i < nVertices; ++i){
        distancias[i].resize(nVertices, LONG_LONG_MAX);
        distancias[i][i] = 0;
    }

    //Verifica quais valores já foram verificados
    vector<int> testado(nVertices, -1);

    //Realiza os testes
    for(int i = 0; i < nTestes; ++i){
        int origem, destino;
        cin >> origem >> destino;
        --origem;
        --destino;

        //Verifica se já verificou as distâncias para do vértice desejado
        if(testado[origem] == -1){
            //Algoritmo de Dijkstra
            priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> fila;
            fila.push(pair<long long,int> (0,origem));
            while(!fila.empty()){
                //Lê o primeiro elemento da fila
                pair<long long,int> frente = fila.top();
                fila.pop();
                long long distFrente = frente.first, u = frente.second;

                //Verifica se é necessário continuar a verificação
                if(distFrente > distancias[origem][u] || distancias[origem][u] == LONG_LONG_MAX){
                    continue;
                }

                //Verifica os próximos vértices
                int nBuscas = grafo[u].size();
                for(int v = 0; v < nBuscas; ++v){
                    long long dist = distancias[origem][u] + grafo[u][v].first;
                    int vertice = grafo[u][v].second;

                    //Atualiza os valores das distâncias
                    if(dist < distancias[origem][vertice]){
                        distancias[origem][vertice] = dist;
                        fila.push(pair<long long,int> (dist, vertice));
                    }
                }
            }

            //Marca que já foram testadas as distâncias para esse vértice
            testado[origem] = 0;
        }

        //Imprime o resultado
        if(distancias[origem][destino] != LONG_LONG_MAX){
            cout << distancias[origem][destino] << '\n';
        }
        else{
            cout << -1 << '\n';
        }
    }

    return 0;
}
