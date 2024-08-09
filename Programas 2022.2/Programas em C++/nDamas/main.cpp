#include <iostream>
#include <array>

using namespace std;

//Salva o tamanho do tabuleiro
#define tamanhoTabuleiro 8

//Salva os valores para verificar as posições onde as damas podem ser colocadas
typedef struct{
    bool verticais[tamanhoTabuleiro];
    bool diagonaisED[(2 * tamanhoTabuleiro) - 1];
    bool diagonaisDE[(2 * tamanhoTabuleiro) - 1];
}Validades;

//Testa com uma dama em cada uma das posições da 1ª linha
void verifica(array<array<int,tamanhoTabuleiro>,tamanhoTabuleiro> &tabuleiro, int &maximo);

//Testa colocar damas em todas as outras posições
void testa(array<array<int,tamanhoTabuleiro>,tamanhoTabuleiro> &tabuleiro, int y,
           int valor, int &maximo, Validades &validades);

int main() {
    //Lê o número de casos
    int nCasos;
    cin >> nCasos;

    for(int n = 0; n < nCasos; ++n){
        array<array<int, tamanhoTabuleiro>, tamanhoTabuleiro> tabuleiro;

        //Lê o tabuleiro
        for(int i = 0; i < tamanhoTabuleiro; ++i){
            for(int j = 0; j < tamanhoTabuleiro; j++){
                cin >> tabuleiro[i][j];
            }
        }

        int maximo = 0;

        //Acha o máximo
        verifica(tabuleiro, maximo);

        //Imprime o resultado formatado
        char buffer[6];
        sprintf(buffer, "%5d", maximo);
        cout << buffer << '\n';
    }

    return 0;
}

void verifica(array<array<int,tamanhoTabuleiro>,tamanhoTabuleiro> &tabuleiro, int &maximo){

    Validades validades {};
    for(int x = 0; x < tamanhoTabuleiro; ++x){
        int diagonalED = x + tamanhoTabuleiro - 1;
        int diagonalDE = x;

        //Marca todas as posições afetadas pela nova dama
        validades.verticais[x] = true;
        validades.diagonaisED[diagonalED] = true;
        validades.diagonaisDE[diagonalDE] = true;

        testa(tabuleiro, 1, tabuleiro[0][x], maximo, validades);

        //Desmarca todas as posições afetadas pela dama
        validades.verticais[x] = false;
        validades.diagonaisED[diagonalED] = false;
        validades.diagonaisDE[diagonalDE] = false;
    }
}

void testa(array<array<int,tamanhoTabuleiro>,tamanhoTabuleiro> &tabuleiro, int y,
           int valor, int &maximo, Validades &validades){

    //Verifica se checou
    if(y == tamanhoTabuleiro){
        if(valor > maximo){
            maximo = valor;
        }
    }
    else for(int x = 0; x < tamanhoTabuleiro; ++x){
            int diagonalED = x - y + tamanhoTabuleiro - 1;
            int diagonalDE = x + y;

            //Verifica se pode colocar uma dama nessa posição
            if(!(validades.verticais[x] || validades.diagonaisED[diagonalED] || validades.diagonaisDE[diagonalDE])){
                //Marca todas as posições afetadas pela nova dama
                validades.verticais[x] = true;
                validades.diagonaisED[diagonalED] = true;
                validades.diagonaisDE[diagonalDE] = true;

                testa(tabuleiro, y + 1, valor + tabuleiro[y][x], maximo, validades);

                //Desmarca todas as posições afetadas pela dama
                validades.verticais[x] = false;
                validades.diagonaisED[diagonalED] = false;
                validades.diagonaisDE[diagonalDE] = false;
            }
    }

}