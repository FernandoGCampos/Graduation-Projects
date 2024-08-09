#include <iostream>
#include <array>
#include <vector>

using namespace std;

int testa(int y, int x, string &palavra1, string &palavra2, vector<vector<int>> &memoria, array<int, 26> &pesos);

int main() {
    //Lê os tamanhos das palavras e os pesos
    int tam1, tam2;
    cin >> tam1 >> tam2;

    //Lê os pesos
    array<int, 26> pesos;
    for(int i = 0; i < 26; ++i){
        cin >> pesos[i];
    }
    cin.ignore(2, '\n');

    //Lê as palavras
    string palavra1;
    palavra1.resize(tam1+1);
    string palavra2;
    palavra1.resize(tam2+1);

    getline(cin, palavra1);
    getline(cin, palavra2);
    palavra2[tam2] = '\0';

    //Inicializa a memória
    vector<vector<int>> memoria(tam1+1);
    for(int i = 0; i < tam1; ++i){
        memoria[i].resize(tam2+1);
        for(int j = 0; j < tam2; ++j){
            memoria[i][j] = -1;
        }
        memoria[i][tam2] = 0;
    }

    memoria[tam1].resize(tam2+1);
    for(int j = 0; j <= tam2; ++j){
        memoria[tam1][j] = 0;
    }

    //Testa
    int maximo = testa(0, 0, palavra1, palavra2, memoria, pesos);
    cout << maximo << '\n';

    return 0;
}

int testa(int y, int x, string &palavra1, string &palavra2, vector<vector<int>> &memoria, array<int, 26> &pesos){
    //Verifica se as letras são iguais
    if(palavra1[y] == palavra2[x]){
        int valor = pesos[palavra1[y] - 'a'];
        if(memoria[y+1][x+1] == -1){
            valor += testa(y+1, x+1, palavra1, palavra2, memoria, pesos);
        }
        else{
            valor += memoria[y+1][x+1];
        }

        memoria[y][x] = valor;
        return valor;
    }
    else{
        //Testa trocar a letra
        int maximo;
        if(memoria[y+1][x+1] == -1){
            maximo = testa(y+1, x+1, palavra1, palavra2, memoria, pesos);
        }
        else{
            maximo = memoria[y+1][x+1];
        }

        //Testa adicionar uma letra
        int maxAdi;
        if(memoria[y][x+1] == -1){
            maxAdi = testa(y, x+1, palavra1, palavra2, memoria, pesos);
        }
        else{
            maxAdi = memoria[y][x+1];
        }
        if(maxAdi > maximo){
            maximo = maxAdi;
        }

        //Testa remover um letra
        int maxDel;
        if(memoria[y+1][x] == -1){
            maxDel = testa(y+1, x, palavra1, palavra2, memoria, pesos);
        }
        else{
            maxDel = memoria[y+1][x];
        }

        if(maxDel > maximo){
            maximo = maxDel;
        }

        memoria[y][x] = maximo;
        return maximo;
    }
}