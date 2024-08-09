#include <iostream>
#include <vector>

using namespace std;

#define MOD 1000000007

int calcula(int x, int y, vector<vector<int>> &quantidades);

int main() {
    //Lê as dimensões da matriz
    int altura, largura;
    cin >> altura >> largura;
    cin.ignore();

    //Lê a matriz
    char buffer;
    vector<vector<int>> quantidades(altura+1);
    for(int i = 0; i < altura; ++i){
        quantidades[i].resize(largura+1);
        for(int j = 0; j < largura; ++j){
            cin >> buffer;
            if(buffer == '#'){
                quantidades[i][j] = 0;
            }
            else{
                quantidades[i][j] = -1;
            }
        }
        //Evita que a recurssão acesse valores fora do limite do ponteiro
        quantidades[i][largura] = 0;
        cin.ignore();
    }

    //Evita que a recurssão acesse valores fora do limite do ponteiro
    quantidades[altura-1][largura-1] = 1;
    quantidades[altura].resize(largura+1);
    for(int k = 0; k <= largura; ++k){
        quantidades[altura][k] = 0;
    }

    //Descobre o número de caminhos
    int maximo = calcula(0, 0, quantidades);
    cout << maximo << '\n';

    return 0;
}

int calcula(int x, int y, vector<vector<int>> &quantidades){
    int maximo = 0;

    //Calcula a quantidade de caminhos se seguir para direita
    if(quantidades[x+1][y] == -1){
        maximo += calcula(x+1, y, quantidades);
    }
    else{
        maximo += quantidades[x+1][y];
    }

    //Calcula a quantidade de caminhos se seguir para baixo
    if(quantidades[x][y+1] == -1){
        maximo += calcula(x, y+1, quantidades);
    }
    else{
        maximo += quantidades[x][y+1];
    }

    //Retorna a quantidade de caminhos
    maximo = maximo % MOD;
    quantidades[x][y] = maximo;
    return maximo;
}
