#include <iostream>
#include <vector>
using namespace std;

long long int calcula(int indice, int final, vector<int> &dias, int *precos, vector<long long int> &custosMinimos, int nDias);

int main() {
    //Lê o número de dias
    int nDias;
    cin >> nDias;

    //Lê os preços dos tickets
    int precos[3];
    for(int i = 0; i < 3; ++i){
        cin >> precos[i];
    }

    //Lê as dias
    vector<int> dias(nDias);
    for(int i = 0; i < nDias; ++i){
        cin >> dias[i];
    }

    //Cria um vetor e inicializa os custos como -1
    vector<long long int> custosMinimos(nDias);
    for(int i = 0; i < nDias; ++i){
        custosMinimos[i] = -1;
    }

    //Calcula o custo para ir da primeira montanha até a útima
    long long int custoMinimo = calcula(0, 0, dias, precos, custosMinimos, nDias);
    cout << custoMinimo << '\n';

    return 0;
}

long long int calcula(int indice, int final, vector<int> &dias, int *precos, vector<long long int> &custosMinimos, int nDias){
    //Verifica se ele comprou para todos os dias
    if(indice >= nDias){
        return 0;
    }
    //Caso o dia já tenha sido pago ele vai para o próximo
    else if(dias[indice] < final){
        return calcula(indice+1, final, dias, precos, custosMinimos, nDias);
    }
    //Caso o dia já tenha sido calculado ele retorna o valor calculado
    else if(custosMinimos[indice] != -1){
        return custosMinimos[indice];
    }
    //Caso ele precise descobrir o custo mínimo a partir deste dia
    else{
        long long int custo1 = precos[0];
        long long int custo2 = precos[1];
        long long int custo3 = precos[2];

        //Testa o próximo dia
        custo1 += calcula(indice+1, dias[indice]+1, dias, precos, custosMinimos, nDias);
        custo2 += calcula(indice+1, dias[indice]+7, dias, precos, custosMinimos, nDias);
        custo3 += calcula(indice+1, dias[indice]+30, dias, precos, custosMinimos, nDias);

        //Verifica qual ticket é melhor
        custosMinimos[indice] = min(custo1, custo2);
        custosMinimos[indice] = min(custosMinimos[indice], custo3);
        return custosMinimos[indice];
    }
}