#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define inf 9223372036854775
//Define os nós do grafo
    typedef struct node_T node;
    struct node_T{
        int nEdges;
        vector<pair<int,long long>> edges;
    };
//Define o grafo
class Graph{
    private:
        vector<vector<unsigned long long>> sPaths;
        void bellmanFord(int start){
            //Vetor que salva quais vértices já foram visitados
            vector<int> visited(nVertices, 0);
            
            //Determina a distância para chegar até ele mesmo como sendo 0
            sPaths[start][start] = 0;

            //Inicia a fila de prioridade
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long,int>>> pQueue;

            //Adiciona o vetor inicial à fila
            pQueue.push(pair<long long,int>(0, start));

            //Itera até que a fila esteja vazia
            while(!pQueue.empty()){
                //Retira o menor elemento da fila
                pair<long long, int> cur = pQueue.top();
                int curVert = cur.second;
                pQueue.pop();

                //Verifica se o vértice já foi visitado
                if(visited[curVert] == 0){
                    //Marca que já visitou esse vértice
                    visited[curVert] = 1;

                    //Verifica todas as arestas do vértice
                    int nCurEdges = vertices[curVert].nEdges;
                    for(int i = 0; i < nCurEdges; ++i){
                        int edgeVert = vertices[curVert].edges[i].first;
                        long long edgeDist = vertices[curVert].edges[i].second;

                        if(sPaths[start][edgeVert] > sPaths[start][curVert] + edgeDist){
                            sPaths[start][edgeVert] = sPaths[start][curVert] + edgeDist;
                            pQueue.push(pair<long long,int>(sPaths[start][edgeVert], edgeVert));
                        }
                    }
                }


            }
        }

    public:
        int nVertices;
        vector<node> vertices;

        Graph(int nVer, int nEdg){
            //Inicializa o grafo
            vertices.resize(nVer);
            nVertices = nVer;

            //Lê as arestas
            for(int i = 0; i < nEdg; ++i){
                int a, b, c;
                cin >> a >> b >> c;
                --a;
                --b;

                //Verifica se já existe uma aresta entre os vértices
                bool found = true;
                for(int i = 0; i < vertices[a].nEdges && found; ++i){
                    if(vertices[a].edges[i].first == b){
                        found = false;
                        if(vertices[a].edges[i].second > c){
                            vertices[a].edges[i].second = c;
                        }
                    }
                }

                //Adiciona a aresta
                if(found){
                    ++vertices[a].nEdges;
                    vertices[a].edges.push_back(pair<int, long long>(b, c));
                }
                

                //Verifica se já existe uma aresta entre os vértices
                found = true;
                for(int i = 0; i < vertices[b].nEdges && found; ++i){
                    if(vertices[b].edges[i].first == a){
                        found = false;
                        if(vertices[b].edges[i].second > c){
                            vertices[b].edges[i].second = c;
                        }
                    }
                }
                //Adiciona a aresta
                if(found){
                    ++vertices[b].nEdges;
                    vertices[b].edges.push_back(pair<int,long long>(a, c));
                }
            }

            //Inicializa o vetor de distâncias
            sPaths.resize(nVertices, vector<unsigned long long>(nVertices, inf));
        }

        long long findMinPath(int start, int end){
            //Verifica se já foram encontradas as distâncias para o dado nó de início
            if(sPaths[start][start]){
                bellmanFord(start);
            }

            //Retorna a distância mínima
            return sPaths[start][end];
        }
};

int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    Graph graph(n, m);

    for(int k = 0; k < q; ++k){
        int a, b;
        cin >> a >> b;
        --a;
        --b;

        //Imprime o caminho mínimo
        long long min = graph.findMinPath(a, b);
        if(min == inf){
            min = -1;
        }

        cout << min << '\n';
    }
    return 0;
}