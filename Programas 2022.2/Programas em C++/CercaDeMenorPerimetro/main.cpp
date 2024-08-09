#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>

using namespace std;

//Calcula a distância entre dois pontos
double calculaDist(pair<long long,long long> &pontoA, pair<long long,long long> &pontoB);

//Compara os ângulis entre os três pontos
bool comparaAng(pair<long long,long long> &pontoA, pair<long long,long long> &pontoB, pair<long long,long long> &pontoC);

//Calculas o perimetro dos pontos que estã em cima
double superior(vector<pair<long long,long long>> &pontos, int nPontos);

//Calculas o perimetro dos pontos que estã em baixo
double inferior(vector<pair<long long,long long>> &pontos, int nPontos);

//Calculas o perimetro dos pontos
double calcula(vector<pair<long long,long long>> &pontos, int nPontos);

int main() {
    //Lê o número de pontos
    int nPontos;
    cin >> nPontos;

    //Cria o vetor para armazenar os pontos
    vector<pair<long long,long long>> pontos;
    pontos.reserve(nPontos);
    for(int i = 0; i < nPontos; ++i){
        //Lê o ponto e o adiciona ao buffer
        long long bufferx, buffery;
        cin >> bufferx >> buffery;
        pontos.push_back(pair<long long,long long> (bufferx, buffery));
    }
    //Ordena os pontos
    sort(pontos.begin(), pontos.end());

    //Verifica o perimetro
    double perimetro = calcula(pontos, nPontos);
    cout << fixed << setprecision(6) << perimetro << "\n";

    return 0;
}

double calculaDist(pair<long long,long long> &pontoA, pair<long long,long long> &pontoB){
    long long x = pontoA.first - pontoB.first;
    long long y = pontoA.second - pontoB.second;
    return sqrt((x * x) + (y * y));
}

bool comparaAng(pair<long long,long long> &pontoA, pair<long long,long long> &pontoB, pair<long long,long long> &pontoC){
    long long ax = pontoB.first - pontoA.first;
    long long ay = pontoB.second - pontoA.second;
    long long cx = pontoC.first - pontoB.first;
    long long cy = pontoC.second - pontoB.second;

    long long buffer = (ax * cy) - (ay * cx);

    return buffer <= 0;
}

double superior(vector<pair<long long,long long>> &pontos, int nPontos){
    vector<pair<long long,long long>> pontosValidos;
    pontosValidos.reserve(nPontos);
    pontosValidos.push_back(pontos[nPontos-1]);
    pontosValidos.push_back(pontos[nPontos-2]);
    int tamanho = 2;
    for(int i = nPontos - 3; i >= 0; --i){
        while(tamanho >= 2){
            if(comparaAng(pontosValidos[tamanho - 2], pontosValidos[tamanho - 1], pontos[i])){
                pontosValidos.pop_back();
                --tamanho;
            }
            else{
                break;
            }
        }
        pontosValidos.push_back(pontos[i]);
        ++tamanho;
    }

    double perimetro = 0;
    for(int i = 1; i < tamanho; ++i){
        perimetro += calculaDist(pontosValidos[i-1], pontosValidos[i]);
    }
    return perimetro;
}

double inferior(vector<pair<long long,long long>> &pontos, int nPontos){
    vector<pair<long long,long long>> pontosValidos;
    pontosValidos.reserve(nPontos);
    pontosValidos.push_back(pontos[0]);
    pontosValidos.push_back(pontos[1]);
    int tamanho = 2;
    for(int i = 2; i < nPontos; ++i){
        while(tamanho >= 2){
            if(comparaAng(pontosValidos[tamanho - 2], pontosValidos[tamanho - 1], pontos[i])){
                pontosValidos.pop_back();
                --tamanho;
            }
            else{
                break;
            }
        }
        pontosValidos.push_back(pontos[i]);
        ++tamanho;
    }

    double perimetro = 0;
    for(int j = 1; j < tamanho; ++j){
        perimetro += calculaDist(pontosValidos[j-1], pontosValidos[j]);
    }
    return perimetro;
}

double calcula(vector<pair<long long,long long>> &pontos, int nPontos) {
    double perimetro = superior(pontos, nPontos);
    perimetro += inferior(pontos, nPontos);
    return perimetro;
}