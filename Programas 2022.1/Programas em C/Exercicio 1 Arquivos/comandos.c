#include "comandos.h"

void comando1(){
    //Abre o arquivo e para o comando caso não consiga abri-lo
    char* nome_do_arquivo = readline();
    FILE* arquivo = fopen(nome_do_arquivo, "wb");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo\n\n");
        free(nome_do_arquivo);
        return;
    }

    //Adiciona todas as pessoas
    int repeticoes;
    scanf("%d ", &repeticoes);
    for(int i = 0; i < repeticoes; ++i){
        adiciona_pessoa(arquivo);
    }

    //Imprime a saída
    fclose(arquivo);
    binarioNaTela(nome_do_arquivo);

    free(nome_do_arquivo);
}

void comando2(){
    //Abre o arquivo e para o comando caso não consiga abri-lo
    char* nome_do_arquivo = readline();
    FILE* arquivo = fopen(nome_do_arquivo, "rb");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo\n\n");
        free(nome_do_arquivo);
        return;
    }

    //Imprime os registros de todas as pessoas
    char teste[1];
    while(fread(teste, 1, 1, arquivo) != 0) {
        ungetc(teste[0], arquivo);
        imprime_registro(arquivo);
    }

    free(nome_do_arquivo);
    fclose(arquivo);
}

void comando3(){
    //Abre o arquivo e para o comando caso não consiga abri-lo
    char* nome_do_arquivo = readline();
    FILE* arquivo = fopen(nome_do_arquivo, "rb");
    if(arquivo == NULL){
        printf("Falha no processamento do arquivo\n");
        free(nome_do_arquivo);
        return;
    }

    //Move o ponteiro para o registro desejado, em caso de o registro não existir ele para o comando
    int RNN;
    scanf("%d ", &RNN);
    if(fseek(arquivo, 238 * RNN, SEEK_SET) != 0){
        printf("“Não foi possível ler o arquivo\n");
        free(nome_do_arquivo);
        fclose(arquivo);
        return;
    }

    //Imprime o registro
    imprime_registro(arquivo);

    free(nome_do_arquivo);
    fclose(arquivo);
}