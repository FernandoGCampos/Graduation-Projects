#include <iostream>
#include <istream>
#include <bitset>

using namespace std;
bitset<32> primo(131071);

int main() {
    //Inicializa o número binário
    bitset<32> numero;

    //Testa para ver se chegou ao final do arquivo
    char buffer;
    while(cin >> buffer){
        //Cria valores iniciais para um número
        numero.reset();

        //Lê os bits
        while(true){
            //Lê 1 bit
            numero <<= 1;
            if(buffer == '1'){
                numero.set(0);
            }
            else if(buffer!= '0'){
                cout << "ERRO " << buffer << '\n';
            }

            //Reduz o número com bas no primo
            while(numero[17]){
                numero = numero.to_ulong() - primo.to_ulong();
            }

            //Testa para ver se encontrou o '#'
            cin >> buffer;
            if(buffer == '#'){
                cin.ignore(2, '\n');
                break;
            }
            else if(buffer == '\n'){
                cin >> buffer;
            }
        }
        if(numero == 0 || numero == 131071){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }
    return 0;
}
