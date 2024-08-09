#include <iostream>
#include <vector>

using namespace std;

//Define os nós do grafo
    typedef struct node_T node;
    struct node_T{
        int color;
        int nEdges;
        vector<int> edges;
    };
//Define o grafo
class Graph{
    private:

    public:
        int nVertices;
        vector<node> vertices;

        Graph(int nVer, int nEdg){
            //Inicializa o grafo
            vertices.resize(nVer);
            nVertices = nVer;
            for(int i = 0; i < nVertices; ++i){
                vertices[i].color = 0;
            }

            //Lê as arestas
            for(int i = 0; i < nEdg; ++i){
                int a, b;
                cin >> a >> b;
                --a;
                --b;

                ++vertices[a].nEdges;
                vertices[a].edges.push_back(b);

                ++vertices[b].nEdges;
                vertices[b].edges.push_back(a);
            }
        }

        bool colorEdges(int vertice){
            for(int i = 0; i < vertices[vertice].nEdges; ++i){
                int curVert = vertices[vertice].edges[i];
                if(vertices[curVert].color){
                    if(vertices[curVert].color == vertices[vertice].color){
                        return false;
                    }
                }
                else{
                    vertices[curVert].color = vertices[vertice].color ^ 3;
                    bool valid = colorEdges(curVert);
                    if(!valid){
                        return false;
                    }
                }
            }
            return true;
        }
};

int main()
{
    int n, m;
    cin >> n >> m;
    Graph graph(n, m);

    bool possible = true;
    for(int i = 0; i < n && possible; ++i){
        if(!graph.vertices[i].color){
            graph.vertices[i].color = 1;
            possible &= graph.colorEdges(i);
        }
    }
    

    if(possible){
        for(int i = 0; i < graph.nVertices; ++i){
            cout << graph.vertices[i].color << ' ';
        }
        cout << '\n';
    }
    else{
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}