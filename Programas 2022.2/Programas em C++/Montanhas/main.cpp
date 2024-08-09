#include <iostream>
#include <vector>
using namespace std;

long long int calcula(int indice, vector<int> &montanhas, vector<long long int> &custosMinimos);

int main() {
    //Lê o número de montanhas
    int nMontanhas;
    cin >> nMontanhas;

    //Lê as montanhas e faz uma cópia da última (evita verificar se chegou no final)
    vector<int> montanhas(nMontanhas+1);
    for(int i = 0; i < nMontanhas; ++i){
        cin >> montanhas[i];
    }
    montanhas[nMontanhas] = montanhas[nMontanhas-1];

    //Cria um vetor e inicializa os custos como -1
    vector<long long int> custosMinimos(nMontanhas+1);
    for(int i = 0; i < nMontanhas; ++i){
        custosMinimos[i] = -1;
    }

    //A última montanha possui custo 0
    custosMinimos[nMontanhas-1] = 0;
    custosMinimos[nMontanhas] = 0;

    //Calcula o custo para ir da primeira montanha até a útima
    long long int custoMinimo = calcula(0, montanhas, custosMinimos);
    cout << custosMinimos[0] << '\n';

    return 0;
}

long long int calcula(int indice, vector<int> &montanhas, vector<long long int> &custosMinimos){
    //Verifica se o resultado da primeira montanha foi encontrado
    long long int custo1 = abs(montanhas[indice] - montanhas[indice+1]);
    if(custosMinimos[indice+1] != -1){
        custo1 += custosMinimos[indice+1];
    }
    else{
        //Calcula o custo para ir da montanha até o final
        custo1 += calcula(indice+1, montanhas, custosMinimos);
    }

    //Verifica se o resultado da segunda montanha foi encontrado
    long long int custo2 = abs(montanhas[indice] - montanhas[indice+2]);
    if(custosMinimos[indice+2] != -1){
        custo2 += custosMinimos[indice+2];
    }
    else{
        //Calcula o custo para ir da montanha até o final
        custo2 += calcula(indice+2, montanhas, custosMinimos);
    }

    //Verifica qual dos dois caminhos possui custo menor
    if(custo1 < custo2){
        custosMinimos[indice] = custo1;
        return custo1;
    }
    else{
        custosMinimos[indice] = custo2;
        return custo2;
    }
}