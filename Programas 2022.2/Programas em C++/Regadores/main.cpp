#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

//Salva as informações de um regador
class Regador {
 public:
    double inicio;
    double fim;

    Regador(double largura, double centro, double raio) {
        double distCentro;
        distCentro = sqrt(pow(raio, 2) - largura);

        inicio = centro - distCentro;
        fim = centro + distCentro;
    }

    bool operator<(Regador const &other){
        return this->inicio < other.inicio;
    }
};

int main() {
    //Lê o número de regadores e para no final do arquivo
    int nRegadores;
    while(cin >> nRegadores){
        //Lê o comprimento da faixa
        double comprimento;
        cin >> comprimento;

        //Lê a largura da faixa e converte ela para o valor usado na fórmula de Pitágoras
        double largura;
        cin >> largura;
        largura /= 2;

        double largPit = largura;
        largPit = pow(largura, 2);

        //Lê os regadores e os ordena de acordo com o ponto de início
        vector<Regador> regadores;
        int nRegVal = 0;
        for(int i = 0; i < nRegadores; ++i){
            double centro;
            cin >> centro;

            double raio;
            cin >> raio;

            if(raio > largura){
                regadores.push_back(Regador(largPit, centro, raio));
                ++nRegVal;
            }
        }
        sort(regadores.begin(), regadores.end());

        //Conta quantos regadores são necessários
        int minRegadores = 0;
        double minimo = 0;

        //Verifica todos os regadores até encontrar o minimo necessário
        int proxReg = 0;
        double maximo = 0;
        while(proxReg < nRegVal){
            //Procura pela maior cobertura possível que não deixe espaços da esquerda para a direita
            while(regadores[proxReg].inicio <= minimo && proxReg < nRegVal){
                if(regadores[proxReg].fim > maximo){
                    maximo = regadores[proxReg].fim;
                }
                ++proxReg;
            }

            //Caso não encontre um regadore que não deixe espaços, interrompe a loop
            if(maximo <= minimo){
                break;
            }

            //Verifica se já encontrou o número necessário
            else if(maximo >= comprimento){
                ++minRegadores;
                break;
            }

            //Caso encontre algum regador, ele adicona o que possui maior cobertura
            else{
                ++minRegadores;
                minimo = maximo;
            }
        }

        //Informa que é impossível preencher o espaço
        if(maximo < comprimento){
            cout << -1 << endl;
        }

        //Informa o número mínimo de regadores
        else{
            cout << minRegadores << endl;
        }
    }
    return 0;
}
