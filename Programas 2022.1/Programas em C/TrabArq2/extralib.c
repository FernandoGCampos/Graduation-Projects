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
    fseek(file, 0, SEEK_SET);
    char status;
    fread(&status, 1, 1, file);
    if(status != '1'){
        printf(ERROR_MSG);
        exit(EXIT_SUCCESS);
    }
    ungetc(status, file);
}

//Creates a copy of the entire file as a .txt (used to debug)
void convertsFile1(char *binFileName){
    //Opens the binary file
    FILE* file = fopen(binFileName, "rb");

    //Creates a empty text file
    int fileNameSize = strlen(binFileName);
    binFileName[fileNameSize - 3] = 't';
    binFileName[fileNameSize - 2] = 'x';
    binFileName[fileNameSize - 1] = 't';
    FILE* newFile = fopen(binFileName, "w+");

    //Buffers
    char charBuffer;
    int intBuffer;

    //Reads the status
    fread(&charBuffer, 1, 1, file);
    fprintf(newFile, "Status: %c\n", charBuffer);

    //Reads the top
    fread(&intBuffer, 4, 1, file);
    fprintf(newFile, "Topo: %d\n", intBuffer);

    //Reads the header
    fprintf(newFile, "Cabeçalho: ");
    for(int i = 5; i < 174; ++i){
        fread(&charBuffer, 1, 1, file);
        fprintf(newFile, "%c", charBuffer);
    }
    fprintf(newFile, "\n");

    //Reads the next RRN to add a register
    fread(&intBuffer, 4, 1, file);
    fprintf(newFile, "Próximo RRN: %d\n", intBuffer);

    //Reads the number of removed registers
    fread(&intBuffer, 4, 1, file);
    fprintf(newFile, "Número removidos: %d\n\n", intBuffer);

    //Reads the registers
    int counter = 0;
    while(fread(&charBuffer, 1, 1, file) != 0){
        //Writes the RRN of the register
        intBuffer = counter;
        fprintf(newFile, "RRN: %d\n", intBuffer);

        //Writes the status of the register
        fprintf(newFile, "Status: %c\n", charBuffer);

        //Counts how many spaces are left in the register
        int regSize = 78;

        //Reads the next logically removed register's RRN
        fread(&intBuffer, 4, 1, file);
        fprintf(newFile, "Próximo: %d\n", intBuffer);

        //Saves the data of the register
        struct data curData = newNullData();
        //Reads the integers
        fread(&curData.id, 4, 1, file);
        fread(&curData.year, 4, 1, file);
        fread(&curData.qtt, 4, 1, file);
        //Reads the initials
        char buffer = '\0';
        fread(&buffer, 1, 1, file);
        curData.initials[0] = buffer;
        if(buffer == '$') {
            curData.initials[0] = '\0';
        }
        fread(&buffer, 1, 1, file);
        curData.initials[1] = buffer;
        if(buffer == '$') {
            curData.initials[1] = '\0';
        }
        curData.initials[2] = '\0';
        //Reads the variable size values
        int counterStrings = 0;
        while(regSize > 4 && counterStrings < 3) {
            buffer = '\0';
            if(fread(&buffer, 1, 1, file) == 0 || buffer == '$') {
                fseek(file, -1, SEEK_CUR);
                break;
            }

            fseek(file, -1, SEEK_CUR);
            ++counterStrings;
            char code = counterStrings;
            int size = 0;
            char* string = readBiString(&code, &size, file);
            if(size > 0) {
                regSize -= 5;
                regSize -= size;
            }

            switch(code) {
                case '0': {
                    if(curData.city == NULL) {
                        curData.city = string;
                    }
                }
                    break;

                case '1': {
                    if(curData.brand == NULL) {
                        curData.brand = string;
                    }
                }
                    break;

                case '2': {
                    if(curData.model == NULL) {
                        curData.model = string;
                    }
                }
                    break;

                default: {
                    printf(ERROR_MSG);
                    exit (EXIT_SUCCESS);
                }
            }
        }

        //Prevents double freeing memory
        if(curData.city == NULL) {
            curData.city = malloc(1);
            curData.city[0] = '\0';
        }
        if(curData.brand == NULL) {
            curData.brand = malloc(1);
            curData.brand[0] = '\0';
        }
        if(curData.model == NULL) {
            curData.model = malloc(1);
            curData.model[0] = '\0';
        }

        //Writes the data
        fprintf(newFile, "ID: %d\n", curData.id);
        fprintf(newFile, "Ano: %d\n", curData.year);
        fprintf(newFile, "Quantidade: %d\n", curData.qtt);
        fprintf(newFile, "Sigla: %s\n", curData.initials);
        fprintf(newFile, "Cidade: %s\n", curData.city);
        fprintf(newFile, "Marca: %s\n", curData.brand);
        fprintf(newFile, "Modelo: %s\n", curData.model);

        //Writes the null values
        fprintf(newFile, "Lixo: ");
        for(int i = regSize; i > 0; --i){
            fread(&charBuffer, 1, 1, file);
            fprintf(newFile, "%c", charBuffer);
        }
        fprintf(newFile, "\n\n");

        //Free the data
        freeData(&curData);

        //Increments the RRN counter
        ++counter;
    }

    //Close the files
    fclose(file);
    fclose(newFile);
}

//Creates a copy of the entire file as a .txt (used to debug)
void convertsFile2(char *binFileName){
    //Opens the binary file
    FILE* file = fopen(binFileName, "rb");

    //Creates a empty text file
    int fileNameSize = strlen(binFileName);
    binFileName[fileNameSize - 3] = 't';
    binFileName[fileNameSize - 2] = 'x';
    binFileName[fileNameSize - 1] = 't';
    FILE* newFile = fopen(binFileName, "w+");

    //Buffers
    char charBuffer;
    int intBuffer;
    long int longBuffer;

    //Reads the status
    fread(&charBuffer, 1, 1, file);
    fprintf(newFile, "Status: %c\n", charBuffer);

    //Reads the top
    fread(&longBuffer, 8, 1, file);
    fprintf(newFile, "Topo: %ld\n", longBuffer);

    //Reads the header
    fprintf(newFile, "Cabeçalho: ");
    for(int i = 9; i < 178; ++i){
        fread(&charBuffer, 1, 1, file);
        fprintf(newFile, "%c", charBuffer);
    }
    fprintf(newFile, "\n");

    //Reads the next byte offset to add a register
    fread(&longBuffer, 8, 1, file);
    fprintf(newFile, "Próximo byte offset: %ld\n", longBuffer);

    //Reads the number of removed registers
    fread(&intBuffer, 4, 1, file);
    fprintf(newFile, "Número removidos: %d\n\n", intBuffer);

    //Reads all registers
    while(fread(&charBuffer, 1, 1, file) != 0 && charBuffer != EOF){
        //Writes The byte offset of the register
        longBuffer = ftell(file) - 1;
        fprintf(newFile, "Offset: %ld\n", longBuffer);

        //Writes the status off the register
        fprintf(newFile, "Status: %c\n", charBuffer);

        //Reads the size of the register
        fread(&intBuffer, 4, 1, file);
        fprintf(newFile, "Tamanho: %d\n", intBuffer);

        //Counts how many spaces are left in the register
        int regSize = intBuffer;
        regSize -= 22;

        //Reads the byte offset of the next logically removed register
        fread(&longBuffer, 8, 1, file);
        fprintf(newFile, "Próximo: %ld\n", longBuffer);

        //Saves the data of the register
        struct data curData = newNullData();
        //Reads the integers
        fread(&curData.id, 4, 1, file);
        fread(&curData.year, 4, 1, file);
        fread(&curData.qtt, 4, 1, file);
        //Reads the initials
        char buffer = '\0';
        fread(&buffer, 1, 1, file);
        curData.initials[0] = buffer;
        if(buffer == '$') {
            curData.initials[0] = '\0';
        }
        fread(&buffer, 1, 1, file);
        curData.initials[1] = buffer;
        if(buffer == '$') {
            curData.initials[1] = '\0';
        }
        curData.initials[2] = '\0';
        //Reads the variable size values
        int counter = 0;
        while(regSize > 4 && counter < 3) {
            buffer = '\0';
            if(fread(&buffer, 1, 1, file) == 0 || buffer == '$') {
                fseek(file, -1, SEEK_CUR);
                break;
            }

            fseek(file, -1, SEEK_CUR);
            ++counter;
            char code = counter;
            int size = 0;
            char* string = readBiString(&code, &size, file);
            if(size > 0) {
                regSize -= 5;
                regSize -= size;
            }

            switch(code) {
                case '0': {
                    if(curData.city == NULL) {
                        curData.city = string;
                    }
                }
                    break;

                case '1': {
                    if(curData.brand == NULL) {
                        curData.brand = string;
                    }
                }
                    break;

                case '2': {
                    if(curData.model == NULL) {
                        curData.model = string;
                    }
                }
                    break;

                default: {
                    printf(ERROR_MSG);
                    exit (EXIT_SUCCESS);
                }
            }
        }

        //Prevents double freeing memory
        if(curData.city == NULL) {
            curData.city = malloc(1);
            curData.city[0] = '\0';
        }
        if(curData.brand == NULL) {
            curData.brand = malloc(1);
            curData.brand[0] = '\0';
        }
        if(curData.model == NULL) {
            curData.model = malloc(1);
            curData.model[0] = '\0';
        }

        //Write the data
        fprintf(newFile, "ID: %d\n", curData.id);
        fprintf(newFile, "Ano: %d\n", curData.year);
        fprintf(newFile, "Quantidade: %d\n", curData.qtt);
        fprintf(newFile, "Sigla: %s\n", curData.initials);
        fprintf(newFile, "Cidade: %s\n", curData.city);
        fprintf(newFile, "Marca: %s\n", curData.brand);
        fprintf(newFile, "Modelo: %s\n", curData.model);

        //Writes the null values
        fprintf(newFile, "Lixo: ");
        for(int i = regSize; i > 0; --i){
            fread(&charBuffer, 1, 1, file);
            fprintf(newFile, "%c", charBuffer);
        }
        fprintf(newFile, "\n\n");

        //Free data
        freeData(&curData);
    }

    //Closes the files
    fclose(file);
    fclose(newFile);
}

//Creates a copy of the entire index file as a .txt (used to debug)
void convertsIndexFile1(char *binFileName){
    //Opens the binary file
    FILE* file = fopen(binFileName, "rb");

    //Creates a empty text file
    int fileNameSize = strlen(binFileName);
    binFileName[fileNameSize - 3] = 't';
    binFileName[fileNameSize - 2] = 'x';
    binFileName[fileNameSize - 1] = 't';
    FILE* newFile = fopen(binFileName, "w+");

    //Buffers
    char charBuffer;
    int intBuffer;

    //Reads the status
    fread(&charBuffer, 1, 1, file);
    fprintf(newFile, "Status: %c\n", charBuffer);

    //Reads all the indexes
    while(fread(&charBuffer, 1, 1, file) != 0){
        fseek(file, -1, SEEK_CUR);

        //Reads the ID
        fread(&intBuffer, 4, 1, file);
        fprintf(newFile, "Id: %d\n", intBuffer);

        //Reads the RRN
        fread(&intBuffer, 4, 1, file);
        fprintf(newFile, "RRN: %d\n\n", intBuffer);
    }

    //Closes both files
    fclose(file);
    fclose(newFile);
}

//Creates a copy of the entire index file as a .txt (used to debug)
void convertsIndexFile2(char *binFileName){
    //Opens the binary file
    FILE* file = fopen(binFileName, "rb");

    //Creates a empty text file
    int fileNameSize = strlen(binFileName);
    binFileName[fileNameSize - 3] = 't';
    binFileName[fileNameSize - 2] = 'x';
    binFileName[fileNameSize - 1] = 't';
    FILE* newFile = fopen(binFileName, "w+");

    //Buffers
    char charBuffer;
    int intBuffer;
    long int longBuffer;

    //Reads the status
    fread(&charBuffer, 1, 1, file);
    fprintf(newFile, "Status: %c\n", charBuffer);

    //Reads all the indexes
    while(fread(&charBuffer, 1, 1, file) != 0){
        fseek(file, -1, SEEK_CUR);

        //Reads the ID
        fread(&intBuffer, 4, 1, file);
        fprintf(newFile, "Id: %d\n", intBuffer);

        //Reads the byte offset
        fread(&longBuffer, 8, 1, file);
        fprintf(newFile, "Offset: %ld\n\n", longBuffer);
    }

    //Closes both files
    fclose(file);
    fclose(newFile);
}

//Creates copies of all files as .txt(used to debug)
void convertsAll(){
    for(int i = 0; i < 8; ++i){
        char *nome = readstring(stdin, ' ');
        convertsFile1(nome);
        free(nome);
    }
    for(int i = 0; i < 8; ++i){
        char *nome = readstring(stdin, ' ');
        convertsIndexFile1(nome);
        free(nome);
    }
    for(int i = 0; i < 9; ++i){
        char *nome = readstring(stdin, ' ');
        convertsFile2(nome);
        free(nome);
    }
    for(int i = 0; i < 9; ++i){
        char *nome = readstring(stdin, ' ');
        convertsIndexFile2(nome);
        free(nome);
    }
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