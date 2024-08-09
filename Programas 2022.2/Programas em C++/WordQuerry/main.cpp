#include <iostream>
#include <string>

using namespace std;

#define MAX 26

typedef struct NO_T{
    struct NO_T *prox[MAX];
    bool ePalavra;
    int palavrasDepois;
} no_t;

no_t* criaNo();

int adicionaPalavra(string &palavra, no_t* atual, int posicao, int tamanho);

int removePalavra(string &palavra, no_t* atual, int posicao, int tamanho);

no_t* achaPalavra(string &palavra);

no_t* raiz = criaNo();

int main() {
    int nOperacoes;
    cin >> nOperacoes;

    for(int i = 0; i < nOperacoes; ++i){
        //Lê a operação e a palavra
        int operacao;
        string palavra;
        cin >> operacao >> palavra;

        switch(operacao){
            case 1:{
                adicionaPalavra(palavra, raiz ,0, palavra.size());
            }
            break;

            case 2:{
                removePalavra(palavra, raiz ,0, palavra.size());
            }
            break;

            case 3:{
                no_t* noPalavra = achaPalavra(palavra);
                if(noPalavra == NULL){
                    cout << "0\n";
                }
                else{
                    cout << noPalavra->palavrasDepois << '\n';
                }
            }
            break;

            default:{
                cout << "A operação \'" << operacao << "\' não existe\n";
            }
        }
    }
    return 0;
}

no_t* criaNo(){
    no_t* novoNo = new no_t;

    //Marca que não se sabe quantas palavras existem depois desse nó
    novoNo->palavrasDepois = 0;

    //Marca que o nó não é o final de uma palavra
    novoNo->ePalavra = false;

    //Inicializa todos os ponteiros para os próximos nós como nulos
    for(int i = 0; i < MAX; ++i){
        novoNo->prox[i] = NULL;
    }

    return novoNo;
}

int adicionaPalavra(string &palavra, no_t* atual, int posicao, int tamanho){
    if(tamanho == posicao){
        if(atual->ePalavra){
            return 0;
        }
        else{
            ++atual->palavrasDepois;
            atual->ePalavra = true;
            return 1;
        }
    }

    //Segue para o próximo nó
    else{
        int indice = palavra[posicao] - 'a';
        if(!atual->prox[indice]){
            atual->prox[indice] = criaNo();
        }
        int adiciona = adicionaPalavra(palavra, atual->prox[indice], posicao+1, tamanho);

        //Incrementa o contador de palavras que existem depois
        atual->palavrasDepois += adiciona;

        return adiciona;
    }
}

int removePalavra(string &palavra, no_t* atual, int posicao, int tamanho){
    if(tamanho == posicao){
        atual->ePalavra = false;
        --atual->palavrasDepois;
        return 1;
    }

    //Procura no próximo nó
    else {
        int indice = palavra[posicao] - 'a';
        if (!atual->prox[indice]) {
            return 0;
        }
        int remove = removePalavra(palavra, atual->prox[indice], posicao + 1, tamanho);

        //Reduz o contador de palavras que existem depois
        if (remove) {
            --atual->palavrasDepois;
        }

        return remove;
    }
}

no_t* achaPalavra(string &palavra){
    int tamanho = palavra.size();

    //Percorre a árvore
    no_t *atual = raiz;
    for(int i = 0; i < tamanho; ++i){
        //Verifica se o próximo nó existe
        int indice = palavra[i] - 'a';
        if(!atual->prox[indice]){
            return NULL;
        }
        atual = atual->prox[indice];
    }

    //Retorna o final a posição do final da palavra
    return atual;
}

int contaPalavras(no_t* atual){
    int quantidade = 0;

    //Verifica se a posição atual marca o final de uma palavra
    if(atual->ePalavra){
        ++quantidade;
    }

    //Verifica todas as palavras que possuem essa como prefixo
    for(int i = 0; i < MAX; ++i){
        if(atual->prox[i]){
            quantidade += contaPalavras(atual->prox[i]);
        }
    }

    return quantidade;
}