#include <iostream>
#include <vector>

using namespace std;

int main() {
    //Lê o tamanho
    int tamanho;
    cin >> tamanho;

    //Lê os números e inicializa os valores das maiores sequências
    vector<int> numeros(tamanho);
    vector<int> maiores(tamanho);
    for(int i = 0; i < tamanho; ++i){
        cin >> numeros[i];
        maiores[i] = -1;
    }
    maiores[0] = 1;

    //Testa as sequências
    int maximo = 1;
    for(int i = 1; i < tamanho; ++i){
        int max = 0;
        for(int j = i-1; j >= 0; --j){
            if(maiores[j] > max && numeros[j] < numeros[i]){
                max = maiores[j];
            }
        }
        maiores[i] = max + 1;
        if(maiores[i] > maximo){
            maximo = maiores[i];
        }
    }

    //Imprime o resultado
    cout << maximo << '\n';

    return 0;
}