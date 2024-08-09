#include <iostream>

using namespace std;

int main() {
    //Lê o número de vértices
    int nVertices;
    cin >> nVertices;

    //Lê o vértice inicial
    int basex, basey;
    cin >> basex >> basey;

    //Salva os valores dos dois últimos vértice lidos
    long long ax, ay, bx, by;
    long long area = 0;

    //Lê todos os vértices
    cin >> ax >> ay;
    ax -= basex;
    ay -= basey;
    for(int i = 2; i < nVertices; ++i){
        //Lê o próximo vértice
        cin >> bx >> by;
        bx -= basex;
        by -= basey;

        //Calcula a área
        area += abs((ax * by) - (ay * bx));

        //Copia o último vértice lido
        ax = bx;
        ay = by;
    }

    //Imprime o resultado
    cout << area << '\n';

    return 0;
}
