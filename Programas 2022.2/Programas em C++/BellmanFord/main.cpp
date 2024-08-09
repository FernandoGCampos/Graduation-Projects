#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    //Lê os números de arestas e de vértices
    int nVertices, nArestas;
    cin >> nVertices >> nArestas;

    //Lê as arestas
    vector<vector<pair<int, int>>> grafo (nVertices);
    for(int i = 0; i < nArestas; ++i){
        int origem, destino;
        long long peso;
        cin >> origem >> destino >> peso;
        grafo[origem-1].push_back(pair<int, long long> (destino-1, peso));
    }

    //Inicializa as distâncias
    vector<long long> distancias(nVertices, LONG_LONG_MAX);
    distancias[0] = 0;

    //Verifica as distâncias
    int repeticoes = nVertices - 1;
    for(int i = 0; i < repeticoes; ++i){
        for(int u = 0; u < nVertices; ++u){
            int nBuscas = grafo[u].size();
            if(distancias[u] < LONG_LONG_MAX){
                for(int v = 0; v < nBuscas; ++v){
                    long long dist = distancias[u] + grafo[u][v].second;
                    int destino = grafo[u][v].first;
                    if(dist < distancias[destino]){
                        distancias[destino] = dist;
                    }
                }
            }
        }
    }

    //Verifica se tem loop negativo
    for(int u = 0; u < nVertices; ++u){
        int nBuscas = grafo[u].size();
        if(distancias[u] < LONG_LONG_MAX) {
            for (int v = 0; v < nBuscas; ++v) {
                long long dist = distancias[u] + grafo[u][v].second;
                int destino = grafo[u][v].first;
                if(dist < distancias[destino]) {
                    cout << "YES\n";
                    return 0;
                }
            }
        }
    }

    cout << "NO\n";
    return 0;
}