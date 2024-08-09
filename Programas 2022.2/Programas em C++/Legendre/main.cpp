#include <iostream>
#include <bitset>
#include <vector>
#include <map>

using namespace std;

#define MAX_CRIVO 46344
#define MAX_P 4792
vector<int> primos;

void criaCrivo(); //Cria uma lista com os primos

void imprimePrimos(); //Imprime os primos

void fatoracao(int numero, map<int, int> &fatores); //Calcula os fatores primos de um número

void imprimeFatores(map<int, int> &fatores); //Imprime os fatores

void aumentaPrimos(int numero);

int main() {
    //Cria um vetor para guardar alguns primos
    criaCrivo();

    //Salva os valores do divisor e do fatorial
    int divisor, fatorial;
    while(cin >> fatorial >> divisor){
        if(divisor == 0){
            cout << divisor << " does not divide " << fatorial << "!\n";
        }
        else if(fatorial >= divisor){
            cout << divisor << " divides " << fatorial << "!\n";
        }
        else if(fatorial == 0){
            if(divisor == 1){
                cout << divisor << " divides " << fatorial << "!\n";
            }
            else{
                cout << divisor << " does not divide " << fatorial << "!\n";
            }
        }
        else{
            //Calcula os fatores do divisor
            map<int, int> fatores;
            fatoracao(divisor, fatores);

            //Verifica se todos os fatores do divisor estão no fatorial
            int divisivel = 1;
            for(map<int, int>::iterator fator = fatores.begin(); fator != fatores.end(); ++fator){
                //Verifica qual a máxima potência do primo que divide o fatorial
                int primo = fator->first;
                long long int tamanho = primo;
                while(fatorial/tamanho >= 1){
                    tamanho *= primo;
                }

                //Verifica a soma dos digitos da representação do fatorial na base do primo
                int fatCopia = fatorial;
                int digitos = 0;
                while(tamanho >= primo){

                    tamanho = tamanho / primo;
                    digitos += (int) fatCopia/tamanho;
                    fatCopia = fatCopia % tamanho;
                }

                //Fórmula de Legendre
                int quantidade = (fatorial-digitos)/(primo-1);

                //Caso o fator não esteja no fatorial
                if(quantidade < fator->second){
                    cout << divisor << " does not divide " << fatorial << "!\n";
                    divisivel = 0;
                    break;
                }
            }
            if(divisivel){
                cout << divisor << " divides " << fatorial << "!\n";
            }
        }
    }
    return 0;
}

void criaCrivo(){
    primos.reserve(MAX_P);
    bitset<MAX_CRIVO> crivo;
    crivo.set();

    //Desconsidera todos os números pares menos o 2
    crivo[0] = crivo[1] = 0;
    primos.push_back(2);
    for(int n = 4; n <= MAX_CRIVO; n+=2){
        crivo[n] = 0;
    }

    //Verifica os números ímpares
    for(long long int i = 3; i <= MAX_CRIVO; i+=2){
        if(crivo[i]){
            primos.push_back(i);
            for(long long int n = i*i; n <= MAX_CRIVO; n+=i){
                crivo[n] = 0;
            }
        }
    }
}

void imprimePrimos(){
    for(int i = 0; i < MAX_P; ++i){
        cout << "primo " << i << " => " << primos[i] << '\n';
    }
}

void fatoracao(int numero, map<int, int> &fatores){
    //Utiliza os primos calculados através do crivo
    int primo;
    for(int i = 0; numero != 1 && i < MAX_P; ++i){
        primo = primos[i];
        while(numero%primo == 0){
            numero /= primo;
            ++fatores[primo];
        }
    }

    if(numero != 1){
        fatores[numero] = 1;
    }
}

void imprimeFatores(map<int, int> &fatores){
    for(map<int, int>::iterator primo = fatores.begin(); primo != fatores.end(); ++primo){
        cout << primo->first << " => " << primo->second << '\n';
    }
}