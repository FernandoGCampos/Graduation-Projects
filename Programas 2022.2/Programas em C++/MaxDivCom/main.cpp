#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void imprimeDiferencas(vector<int> &diferencas);

int main() {
    while(true){
        //Salva os valores
        vector<int> valores;
        valores.reserve(1001);
        int valor;

        //Acaba a execução caso o primeiro valor seja nulo
        cin >> valor;
        if(valor == 0){
            return 0;
        }

        //Lê os valores
        while(valor != 0){
            valores.push_back(valor);
            cin >> valor;
        }
        sort(valores.begin(), valores.end());

        //Inicializa o vetor de diferencas
        int nDiferencas = valores.size()-1;
        vector<int> diferencas;
        diferencas.reserve(nDiferencas);

        //Preenche a primeira versao do vertor de diferencas
        int diferenca;
        int novasDiferencas = 0;
        for(int i = 0; i < nDiferencas; ++i){
            diferenca = valores[i+1] - valores[i];
            if(diferenca){
                ++novasDiferencas;
                diferencas.push_back(diferenca);
            }
        }
        sort(diferencas.begin(), diferencas.end());
        nDiferencas = novasDiferencas;

        //Repete a execução até não poder mais
        int buffer;
        while(nDiferencas > 1){
            novasDiferencas = 1;
            diferenca = 0;
            for(int i = 1; i < nDiferencas; ++i){
                //Salva a diferenca entre os valores
                buffer = (diferencas[i] - diferencas[i-1])%diferencas[0];
                if(diferenca){
                    diferencas[novasDiferencas] = diferenca;
                    ++novasDiferencas;
                }
                diferenca = buffer;
            }
            if(diferenca){
                diferencas[novasDiferencas] = diferenca;
                ++novasDiferencas;
            }
            diferencas.resize(novasDiferencas);
            sort(diferencas.begin(), diferencas.end());
            nDiferencas = novasDiferencas;
        }

        //Imprime o valor desejado
        cout << diferencas[0] << '\n';
    }
}

void imprimeDiferencas(vector<int> &diferencas){
    for(unsigned long int i = 0; i < diferencas.size(); ++i){
        cout << diferencas[i] << ' ';
    }
    cout << '\n';
}