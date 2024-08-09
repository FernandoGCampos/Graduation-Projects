#include <iostream>

using namespace std;

int main() {
    // Lê o número de casos
    int nCasos;
    cin >> nCasos;
    for(int n = 0; n < nCasos; ++n){
        //Lê o número de pilhas
        int nPilhas;
        cin >> nPilhas;

        // Realiza as operações 'XOR' conforme lê o tamanho da cada pilha
        int comparador = 0;
        int buffer;
        for(int i = 0; i < nPilhas; ++i){
            cin >> buffer;
            comparador ^= buffer;
        }

        // Caso o valor seja 0 ele remove um pedra de qualquer uma das pilhas
        if(comparador){
            cout << "0\n";
        }
        else{
            cout << "1\n";
        }

    }

    return 0;
}