//Aluno: Fernando Gonçalves Campos    NºUSP: 12542352

#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <random>
#include <array>
#include <vector>
#include <forward_list>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <unordered_set>
#include <unordered_map>
using namespace std;

using namespace std::chrono;
#define now high_resolution_clock::now()
#define time_point high_resolution_clock::time_point

array<int, 10> tamanhos{10, 100, 1000, 5000, 7500, 10000, 15000, 25000, 37500, 50000};

void testaArrayPre();
void testaVecResizePre();

/* Velocidade para preencher
 *
 *
 * */
int main() {
    testaArrayPre();
    testaVecResizePre();

    return 0;
}

void testaArrayPre(){
    srand(75);
    string nomeArq;
    nomeArq = "ArrayPer.csv";
    ofstream arq;
    arq.open(nomeArq);
    arq << "Tamanho,Tempo\n0,0\n";
    ofstream arqRem;

    {
        time_point comeco = now;
        for(int n = 0; n < 16; ++n){
            array<int, 10> arr;
            for (int i = 0; i < 10; ++i) {
                arr[i] = rand();
            }
        }
        time_point final = now;
        duration<double> duracao = duration_cast<duration<double>>(final - comeco);
        arq << 10 << ',' << (duracao.count()/16) << '\n';
    }
    {
        time_point comeco = now;
        for(int n = 0; n < 16; ++n) {
            array<int, 100> arr;
            for (int i = 0; i < 100; ++i) {
                arr[i] = rand();
            }
        }
        time_point final = now;
        duration<double> duracao = duration_cast<duration<double>>(final - comeco);
        arq << 100 << ',' << (duracao.count()/16) << '\n';
    }
    {
        time_point comeco = now;
        for(int n = 0; n < 16; ++n) {
            array<int, 1000> arr;
            for (int i = 0; i < 1000; ++i) {
                arr[i] = rand();
            }
        }
        time_point final = now;
        duration<double> duracao = duration_cast<duration<double>>(final - comeco);
        arq << 1000 << ',' << (duracao.count()/16) << '\n';
    }
    {
        time_point comeco = now;
        for(int n = 0; n < 16; ++n) {
            array<int, 5000> arr;
            for (int i = 0; i < 5000; ++i) {
                arr[i] = rand();
            }
        }
        time_point final = now;
        duration<double> duracao = duration_cast<duration<double>>(final - comeco);
        arq << 5000 << ',' << (duracao.count()/16) << '\n';
    }
    {
        time_point comeco = now;
        for(int n = 0; n < 16; ++n) {
            array<int, 7500> arr;
            for (int i = 0; i < 7500; ++i) {
                arr[i] = rand();
            }
        }
        time_point final = now;
        duration<double> duracao = duration_cast<duration<double>>(final - comeco);
        arq << 7500 << ',' << (duracao.count()/16) << '\n';
    }
    {
        time_point comeco = now;
        for(int n = 0; n < 16; ++n) {
            array<int, 10000> arr;
            for (int i = 0; i < 10000; ++i) {
                arr[i] = rand();
            }
        }
        time_point final = now;
        duration<double> duracao = duration_cast<duration<double>>(final - comeco);
        arq << 10000 << ',' << (duracao.count()/16) << '\n';
    }
    {
        time_point comeco = now;
        for(int n = 0; n < 16; ++n) {
            array<int, 15000> arr;
            for (int i = 0; i < 15000; ++i) {
                arr[i] = rand();
            }
        }
        time_point final = now;
        duration<double> duracao = duration_cast<duration<double>>(final - comeco);
        arq << 15000 << ',' << (duracao.count()/16) << '\n';
    }
    {
        time_point comeco = now;
        for(int n = 0; n < 16; ++n) {
            array<int, 25000> arr;
            for (int i = 0; i < 25000; ++i) {
                arr[i] = rand();
            }
        }
        time_point final = now;
        duration<double> duracao = duration_cast<duration<double>>(final - comeco);
        arq << 25000 << ',' << (duracao.count()/16) << '\n';
    }
    {
        time_point comeco = now;
        for(int n = 0; n < 16; ++n) {
            array<int, 37500> arr;
            for (int i = 0; i < 37500; ++i) {
                arr[i] = rand();
            }
        }
        time_point final = now;
        duration<double> duracao = duration_cast<duration<double>>(final - comeco);
        arq << 37500 << ',' << (duracao.count()/16) << '\n';
    }
    {
        time_point comeco = now;
        for(int n = 0; n < 16; ++n) {
            array<int, 50000> arr;
            for (int i = 0; i < 50000; ++i) {
                arr[i] = rand();
            }
        }
        time_point final = now;
        duration<double> duracao = duration_cast<duration<double>>(final - comeco);
        arq << 50000 << ',' << (duracao.count()/16) << '\n';
    }

    arq.close();
}

void testaVecResizePre(){
    srand(75);
    string nomeArq;
    nomeArq = "VecResizePer.csv";
    ofstream arq;
    arq.open(nomeArq);
    arq << "Tamanho,Tempo\n0,0\n";
    ofstream arqRem;

    for(int i = 0; i < 10; i++) {
        int tamanho = tamanhos[i];
        time_point comeco = now;
        for(int n = 0; n < 16; ++n) {
            vector<int> vec(tamanho);
            for (int j = 0; j < tamanho; ++j) {
                vec[j] = rand();
            }
        }
        time_point final = now;
        duration<double> duracao = duration_cast<duration<double>>(final - comeco);
        arq << tamanho << ',' << (duracao.count()/16) << '\n';
    }
    arq.close();
}