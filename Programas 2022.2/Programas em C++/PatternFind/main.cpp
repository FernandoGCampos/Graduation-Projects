#include <iostream>
#include <string>
#include <vector>

using namespace std;


void kmpCriaMem(string &chave, vector<int> &kmpMem, int tamChave);

void kmpBusca(string &texto, string &chave, vector<int> &kmpMem, vector<int> &repeticoes, int tamTexto, int tamChave);

int main() {
    int nCasos;
    cin >> nCasos;
    for(int i = 0; i < nCasos; ++i){
        //Lê o texto
        string texto;
        texto.reserve(1024);
        cin >> texto;
        int tamTexto = texto.size();

        //Lê a chave de busca
        string chave;
        chave.reserve(tamTexto);
        cin >> chave;
        int tamChave = chave.size();

        //Ignore o pulo de linha
        cin.ignore(2, '\n');

        //Cria o vetor para salvas as posições para onde se deve voltar
        vector<int> kmpMem(tamChave+1);
        kmpCriaMem(chave, kmpMem, tamChave);

        //Busca pelas posições onde a chave esta presente no texto
        vector<int> repeticoes;
        repeticoes.reserve(128);
        kmpBusca(texto, chave, kmpMem, repeticoes, tamTexto, tamChave);

        //Imprime o resultado
        int nRepeticoes = repeticoes.size();
        if(nRepeticoes){
            cout << nRepeticoes << '\n';
            for(int n = 0; n < nRepeticoes; ++n){
                cout << repeticoes[n] << ' ';
            }
            cout << '\n';
        }
        else{
            cout << "Not Found\n";
        }

        //Imprime o pulo de linha entre casos de teste
        cout << '\n';
    }

    return 0;
}

void kmpCriaMem(string &chave, vector<int> &kmpMem, int tamChave){
    //Inicializa os contadores
    int i = 0, j = -1;
    kmpMem[0] = -1;

    while(i < tamChave){
        //Verifica se todos os valores
        while(j>=0 && chave[i] != chave[j]){
            j = kmpMem[j];
        }

        //Incrementa os contadores
        ++i; ++j;
        kmpMem[i] = j;

        //Evita que ele teste duas vezes uma mesma letra
        if(!j && i!=1){
            kmpMem[i-1] = 0;
        }
    }
}

void kmpBusca(string &texto, string &chave, vector<int> &kmpMem, vector<int> &repeticoes, int tamTexto, int tamChave){
    //Inicializa os contadores
    int i = 0, j = 0;

    while(i < tamTexto){
        //Verifica se todos os valores
        while(j>=0 && texto[i] != chave[j]){
            j = kmpMem[j];
        }

        //Incrementa os contadores
        ++i; ++j;

        //Salva os valores encontrados
        if(j == tamChave){
            repeticoes.push_back(i-j+1);
            j = kmpMem[j];
        }
    }
}