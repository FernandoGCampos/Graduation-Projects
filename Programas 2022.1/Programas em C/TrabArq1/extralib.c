// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that can't be placed in any other file

#include "extralib.h"

//Reads a string in a file until finds a parameter o new line indicator
char* readstring(FILE* file, char parameter) {
    char* string = malloc(0);
    int size = 0;

    //Adds each new character to the string
    char newChar;
    do{
        ++size;
        string = realloc(string, size);
        newChar = fgetc(file);
        string[size-1] = newChar;

    }while(newChar != '\n' &&
           newChar != '\r' &&
           newChar != EOF &&
           newChar != parameter);

    //Remove '\n' from "\r\n"
    if(newChar == '\r') {
        newChar = getchar();
        if(newChar != '\n'){
            ungetc(newChar, file);
        }
    }

    string[size-1] = '\0';
    return string;
}

//Tries to open a file and exits the program if its unable to
FILE* openFile(char *fileName, char *method) {
    FILE *file = fopen(fileName, method);

    if(file == NULL) {
        printf(ERROR_MSG);
        exit(EXIT_SUCCESS);
    }

    return file;
}

//Test file status
void testStatus(FILE* file){
    char status;
    fread(&status, 1, 1, file);
    if(status != '1'){
        printf(ERROR_MSG);
        exit(EXIT_SUCCESS);
    }
    ungetc(status, file);
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