#include <iostream>
#include <vector>

using namespace std;

int testa(int y, int x, string &palavra1, string &palavra2, vector<vector<int>> &memoria);

int main() {
    //Lê o número de casos de teste
    int nTestes;
    cin >> nTestes;
    cin.ignore(2, '\n');

    //Executa os testes
    for(int n = 0; n < nTestes; ++n){
        string palavra1, palavra2;
        getline(cin, palavra1);
        getline(cin, palavra2);
        palavra2[palavra2.length()] = '\n'; // Garante que os \0s não sejam considerados iguais

        //Inicializa a memória
        int tam1 = palavra1.length();
        int tam2 = palavra2.length();
        vector<vector<int>> memoria(tam1+1);
        for(int i = 0; i < tam1; ++i){
            memoria[i].resize(tam2+1);
            for(int j = 0; j < tam2; ++j){
                memoria[i][j] = -1;
            }
            memoria[i][tam2] = tam1 - i;
        }

        memoria[tam1].resize(tam2+1);
        for(int j = 0; j <= tam2; ++j){
            memoria[tam1][j] = tam2 - j;
        }

        int minimo = testa(0, 0, palavra1, palavra2, memoria);
        cout << minimo << '\n';
    }
    return 0;
}

int testa(int y, int x, string &palavra1, string &palavra2, vector<vector<int>> &memoria){
    //Verifica se as letras são iguais
    if(palavra1[y] == palavra2[x]){
        if(memoria[y+1][x+1] == -1){
            memoria[y][x] = testa(y+1, x+1, palavra1, palavra2, memoria);
        }
        else{
            memoria[y][x] = memoria[y+1][x+1];
        }
        return memoria[y][x];
    }
    else{
        //Testa trocar a letra
        int minimo = 1;
        if(memoria[y+1][x+1] == -1){
            minimo += testa(y+1, x+1, palavra1, palavra2, memoria);
        }
        else{
            minimo += memoria[y+1][x+1];
        }

        //Testa adicionar uma letra
        int valAdi = 1;
        if(memoria[y][x+1] == -1){
            valAdi += testa(y, x+1, palavra1, palavra2, memoria);
        }
        else{
            valAdi += memoria[y][x+1];
        }

        if(valAdi < minimo){
            minimo = valAdi;
        }

        //Testa remover um letra
        int valDel = 1;
        if(memoria[y+1][x] == -1){
            valDel += testa(y+1, x, palavra1, palavra2, memoria);
        }
        else{
            valDel += memoria[y+1][x];
        }

        if(valDel < minimo){
            minimo = valDel;
        }

        memoria[y][x] = minimo;
        return minimo;
    }
}