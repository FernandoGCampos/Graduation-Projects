#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;

int main() {
    //Lê os números de containers e verifica se chegou no final do arquivo
    int nContainers{};
    int nSet{1};
    while(cin >> nContainers){

        //Lê o número de massas
        int nMassas{};
        cin >> nMassas;

        //Lê as massas e calcula a média por container
        int massas[nMassas];
        float massaMedia{};
        for(int i = 0; i < nMassas; ++i){
            cin >> massas[i];
            massaMedia += massas[i];
        }
        massaMedia /= nContainers;

        //Ordena as massas em ordem decrescente
        sort(massas, massas + nMassas, greater<>());

        //Adiciona as massas aos containers, e imprime parte da saída
        int containers[nContainers];
        cout << "Set #" << nSet << endl;
        for(int i = 0; i < nContainers; ++i){
            containers[i] = 0;

            cout << " " << i << ": ";

            int j = nContainers*2 - i - 1;
            if(j < nMassas){
                containers[i] += massas[j];
                cout << massas[j] << " ";
            }

            if(i < nMassas){
                containers[i] += massas[i];
                cout << massas[i];
            }

            cout << endl;
        }

        //Calcula o desequilibrio da distribuição
        float desequilibrio{};
        for(int i = 0; i < nContainers; ++i){
            desequilibrio += abs(containers[i] - massaMedia);
        }
        printf("IMBALANCE = %.5f\n\n", desequilibrio);

        ++nSet;
    }
    return 0;
}
