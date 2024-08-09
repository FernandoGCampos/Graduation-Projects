#include "funcoes.h"

char* readline(){
    char* string = malloc(0);
    int size = 0;

    //Adds each new character to the string
    char new_char;
    do{
        ++size;
        string = realloc(string, size);
        new_char = getchar();
        string[size-1] = new_char;
    }while(new_char != '\n' &&
           new_char != '\r' &&
           new_char != EOF);

    //Remove '\n' from "\r\n"
    if(new_char == '\r'){
        new_char = getchar();
        if(new_char != '\n'){
            ungetc(new_char, stdin);
        }
    }

    string[size-1] = '\0';
    return string;
}

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

    /* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
    *  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

    unsigned long i, cs;
    unsigned char *mb;
    size_t fl;
    FILE *fs;
    if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
        fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
        return;
    }
    fseek(fs, 0, SEEK_END);
    fl = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    mb = (unsigned char *) malloc(fl);
    fread(mb, 1, fl, fs);

    cs = 0;
    for(i = 0; i < fl; i++) {
        cs += (unsigned long) mb[i];
    }
    printf("%lf\n", (cs / (double) 100));
    free(mb);
    fclose(fs);
}

void adiciona_pessoa(FILE* arquivo){
    char primeiro_nome[51];
    char ultimo_nome[51];
    char email[81];
    char nacionalidade[51];
    int idade[1];

    scanf("%s ", primeiro_nome);
    scanf("%s ", ultimo_nome);
    scanf("%s ", email);
    scanf("%s ", nacionalidade);
    scanf("%d ", idade);

    fwrite(primeiro_nome, 1, strlen(primeiro_nome) + 1, arquivo);
    for(int i = strlen(primeiro_nome); i < 50; ++i){
        fwrite("$", 1, 1, arquivo);
    }

    fwrite(ultimo_nome, 1, strlen(ultimo_nome) + 1, arquivo);
    for(int i = strlen(ultimo_nome); i < 50; ++i){
        fwrite("$", 1, 1, arquivo);
    }

    fwrite(email, 1, strlen(email) + 1, arquivo);
    for(int i = strlen(email); i < 80; ++i){
        fwrite("$", 1, 1, arquivo);
    }

    fwrite(nacionalidade, 1, strlen(nacionalidade) + 1, arquivo);
    for(int i = strlen(nacionalidade); i < 50; ++i){
        fwrite("$", 1, 1, arquivo);
    }

    fwrite(idade, 4, 1, arquivo);
}

void imprime_registro(FILE* arquivo){
    char primeiro_nome[51];
    char ultimo_nome[51];
    char email[81];
    char nacionalidade[51];
    int idade[1];

    fread(primeiro_nome, 1, 51, arquivo);
    fread(ultimo_nome, 1, 51, arquivo);
    fread(email, 1, 81, arquivo);
    fread(nacionalidade, 1, 51, arquivo);
    fread(idade, 4, 1, arquivo);

    printf("Firstname: %s\n", primeiro_nome);
    printf("Lastname: %s\n", ultimo_nome);
    printf("Email: %s\n", email);
    printf("Nationality: %s\n", nacionalidade);
    printf("Age: %d\n\n", idade[0]);
}

