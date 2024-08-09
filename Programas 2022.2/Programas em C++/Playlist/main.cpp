#include<cmath>
#include <iostream>
using namespace std;

int busca(int &nMusicas, int *musicas, int &tempo);

int buscaBinaria(int min, int max, int *musicas, int &tempo);

int main() {
    //Lê os números de músicas e de tempos
    int nMusicas, nTempos;
    cin >> nMusicas >> nTempos;

    //Lê as músicas (salvas pelo tempo de início)
    int contador = 1;
    int musicas[nMusicas+1];
    musicas[0] = 1;
    for(int i = 1; i <= nMusicas; ++i){
        int duracao, ciclos;
        cin >> duracao >> ciclos;
        contador += duracao * ciclos;
        musicas[i] = contador;
    }

    //Descobre quais músicas estavam tocando
    for(int i = 0; i < nTempos; ++i){
        //Lê os tempos
        int tempo;
        cin >> tempo;

        //Retorna o valor esperado
        int musica = busca(nMusicas, musicas, tempo);
        cout << musica << '\n';
    }

    return 0;
}

int busca(int &nMusicas, int *musicas, int &tempo){
    //Verifica se é a primeira música
    if(musicas[1] > tempo){
        return 1;
    }

    //Verifica se é a última música
    else if(musicas[nMusicas-1] <= tempo && musicas[nMusicas] > tempo){
        return nMusicas;
    }

    //Busca a música através de busca binária
    else{
        return buscaBinaria(0, nMusicas-1, musicas, tempo);
    }
}

int buscaBinaria(int min, int max, int *musicas, int &tempo){
    //Calcula o valor intermediário da parte do vetor
    int med = trunc((min + max)/2);

    //No caso de a música já ter sido tocada
    if(musicas[med] <= tempo){
        if(musicas[med+1] > tempo){
            return med+1;
        }

        //Busca pela música
        else{
            return buscaBinaria(med, max, musicas, tempo);
        }
    }

    //No caso de a música não ter sido tocado no momento
    else if(musicas[med] > tempo){
        //Verifica se a música encontrada vem logo após a musica desejada
        if(musicas[med-1] <= tempo){
            return med;
        }

        //Busca pela música
        else{
            return buscaBinaria(min, med-1, musicas, tempo);
        }
    }
    else{
        return med;
    }
}