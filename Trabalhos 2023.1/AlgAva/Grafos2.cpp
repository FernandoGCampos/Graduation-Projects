#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Define a classe de união
class FindUnion{
    private:
        vector<int> p;
        vector<int> rank;

    public:
        FindUnion(int N){
            p.assign(N, 0);
            rank.assign(N, 0);
            for(int i = 0; i < N; ++i){
                p[i] = i;
            }
        }

        int findSet(int i){
            if(p[i] == i){
                return i;
            }
            else{
                return findSet(p[i]);
            }
        }

        bool isSameSet(int i, int j){
            return (findSet(i) == findSet(j));
        }

        void unionSet(int i, int j){
            int x = findSet(i);
            int y = findSet(j);

            if(x != y){
                if(rank[x] > rank[y]){
                    p[y] = x;
                }
                else{
                    p[x] = y;
                    if(rank[x] == rank[y]){
                        ++rank[y];
                    }
                }
            }
        }
};

//Define o grafo
class Graph{
    public:
        int nVertices;
        int nEdges;
        vector<pair<unsigned long long, pair<int,int>>> edges;

        Graph(int nVer, int nEdg){
            nVertices = nVer;
            edges.reserve(nEdg);
            nEdges = nEdg;

            //Lê as arestas
            for(int i = 0; i < nEdg; ++i){
                int a, b;
                unsigned long long c;
                cin >> a >> b >> c;
                --a;
                --b;
                if(a > b){
                    int buffer = a;
                    a = b;
                    b = buffer;
                }

                edges.push_back(pair<unsigned long long, pair<int,int>>(c, pair<int, int>(a,b)));
            }
        }

        void kruskal(){
            sort(edges.begin(), edges.end());
            
            unsigned long long  minCost = 0;
            FindUnion fu(nVertices);

            for(int i = 0; i < nEdges; ++i){
                pair<unsigned long long , pair<int, int>> front = edges[i];

                if(!fu.isSameSet(front.second.first, front.second.second)){
                    minCost += front.first;

                    fu.unionSet(front.second.first, front.second.second);
                }
            }

            bool found = true;
            for(int i = 1; i < nVertices && found; ++i){
                if(!fu.isSameSet(0, i)){
                    cout << "IMPOSSIBLE\n";
                    found = false;
                }
            }

            if(found){
                cout << minCost << '\n';
            }
        }

        unsigned long long  mstCost = 0;
};

int main()
{
    int n, m;
    cin >> n >> m;
    Graph graph(n, m);

    //Encontra o valor mínimo
    graph.kruskal();

    
    return 0;
}