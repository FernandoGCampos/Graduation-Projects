#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <algorithm>

using namespace std;

sem_t mtx;

int tamanho = 100;
int posicao = 0;
vector<int> valores(tamanho, -1);

void processo(int i){
    sem_wait(&mtx);
    cout << "Colocando o valor " << i << " na posição " << posicao << endl;
    valores[posicao] = i;
    ++posicao;
    sem_post(&mtx);
}

int main() {
    sem_init(&mtx, 0, 1);
    vector<thread> buffer;
    for(int i = 0; i < tamanho; ++i){
        buffer.push_back(thread(processo, i));
    }

    for(int i = 0; i < tamanho; ++i){
        buffer[i].join();
    }
    return 0;
}