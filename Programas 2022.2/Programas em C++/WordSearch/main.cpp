#include <iostream>

using namespace std;

bool testa(int altura, int largura, string *letras, int contador, int tamanho, string palavra,
           int x, int y, int xAnterior, int yAnterior);

int main() {
    int altura, largura;
    cin >> altura >> largura;

    //Lê as letras
    string letras[altura];
    cin.ignore();
    for(int i = 0; i < altura; ++i){
        getline(cin, letras[i]);
    }

    //Lê o tamanho
    int tamanho;
    cin >> tamanho;

    //Lê a palavra
    string palavra;
    cin.ignore();
    getline(cin, palavra);

    //Verifica todas as letras como letras iniciais
    bool achou = false;
    for(int i = 0; i < altura && !achou; ++i){
        for(int j = 0; j < largura && !achou; ++j) {
            achou = testa(altura, largura, letras, 0, tamanho, palavra, j, i, j, i);
        }
    }

    //Imprime o resultado
    if(achou){
        cout << "Yes" << '\n';
    }
    else{
        cout << "No" << '\n';
    }

    return 0;
}

bool testa(int altura, int largura, string *letras, int contador, int tamanho, string palavra,
           int x, int y, int xAnterior, int yAnterior){
    //Se tiver achado a palavra retorna que achou
    if(contador == tamanho - 1 && letras[y][x] == palavra[contador]){
        return true;
    }
    //Se não achar a palavra retorna a recursão
    else if(contador == tamanho || letras[y][x] != palavra[contador]){
        return false;
    }
    //Se for uma letra válida ele segue para a próxima
    else{
        if(x+1 != xAnterior && x < largura - 1){
            if(testa(altura, largura, letras, contador+1, tamanho, palavra, x+1, y, x, y)){
                return true;
            }
        }
        if(x-1 != xAnterior && x > 0){
            if(testa(altura, largura, letras, contador+1, tamanho, palavra, x-1, y, x, y)){
                return true;
            }
        }
        if(y+1 != yAnterior && y < altura - 1){
            if(testa(altura, largura, letras, contador+1, tamanho, palavra, x, y+1, x, y)){
                return true;
            }
        }
        if(y-1 != yAnterior && y > 0){
            if(testa(altura, largura, letras, contador+1, tamanho, palavra, x, y-1, x, y)){
                return true;
            }
        }
        return false;
    }
}
