#include <cmath>
#include <iostream>
using namespace std;

void recursao(int min, int max, int* cordas, long long int& cruzamentos);

int main() {
    //Lê o número de casos
    int nCasos = 0;
    cin >> nCasos;

    //Repete para cada caso
    while(nCasos > 0){
        //Lê o número de cordas
        int tamanho = 0;
        cin >> tamanho;

        //Lê as cordas
        int cordas[tamanho];
        for(int i = 0; i < tamanho; ++i){
            cin >> cordas[i];
        }

        //Calcula o número de cruzamentos
        long long int cruzamentos = 0;
        recursao(0, tamanho-1, cordas, cruzamentos);

        //Imprime o resultado
        cout << cruzamentos << '\n';

        //Decrementa o contador de casos restantes
        --nCasos;
    }
    return 0;
}

void recursao(int min, int max, int* cordas, long long int& cruzamentos){
    //Caso não seja a menor divisão possível
    if(max != min){
        //Salva o meio do vetor (inicializado com o valor usado para vetores de tamanho <= 2)
        int med = min + 1;

        //Continua subdividindo o vetor
        if(max - min >= 2){
            med = trunc((max + min) / 2);
            recursao(min, med, cordas, cruzamentos);
            ++med;
            recursao(med, max, cordas, cruzamentos);
        }

        //Move as cordas para um buffer
        int tamanhoBuffer = max-min+1;
        int medBuffer = med-min;
        int buffer[tamanhoBuffer];
        for(int i = min, n = 0; i <= max; ++i, ++n){
            buffer[n] = cordas[i];
        }

        //Move os valores de volta para o vetor de cordas
        int valEsquerda = 0;
        int valDireita = medBuffer;
        for(int i = min; i <= max; ++i){
            if(valDireita >= tamanhoBuffer || (valEsquerda < medBuffer && buffer[valEsquerda] < buffer[valDireita])){
                cordas[i] = buffer[valEsquerda];
                ++valEsquerda;
            }
            else{
                cordas[i] = buffer[valDireita];
                cruzamentos += min + valDireita - i;
                ++valDireita;
            }
        }
    }
}
