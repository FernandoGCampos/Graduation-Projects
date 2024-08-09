#include <iostream>
#include <string>

using namespace std;

int main() {
    // Lê o número de casos de teste
    int nCasos;
    cin >> nCasos;
    cin.ignore();
    for(int n = 0; n < nCasos; ++n){
        // Lê o texto que será alterado
        string texto;
        cin >> texto;
        cin.ignore(2, '\n');

        // Repete o processo para todos os caracteres do texto
        int tamanhoTexto = texto.size();
        for(int i = 0; i < tamanhoTexto; ++i){
            // Alice altera o próximo caractere válido
            if(texto[i] == 'a'){
                cout << 'b';
            }
            else{
                cout << 'a';
            }

            // Incrementa o contador e verifica se chegou ao final
            ++i;
            if(i == tamanhoTexto){
                break;
            }

            // Bob altera o próximo caractere válido
            if(texto[i] == 'z'){
                cout << 'y';
            }
            else{
                cout << 'z';
            }
        }
        cout << '\n';
    }
    return 0;
}
