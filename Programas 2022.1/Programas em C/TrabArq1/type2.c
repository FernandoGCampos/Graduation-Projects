// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all functions that only work for files of type 2

#include "type2.h"

//Chooses what command to execute
void type2(char command) {
    switch(command) {
        case '1':
            command1_2();
            break;

        case '2':
            command2_2();
            break;

        case '3':
            command3_2();
            break;

        default:
            printf(ERROR_MSG);
    }
}

//Executes the first command
void command1_2() {
    char* inputFileName = readstring(stdin, ' ');
    char* outputFileName = readstring(stdin, ' ');

    FILE* inFile = openFile(inputFileName, "r");
    FILE* outFile = openFile(outputFileName, "wb+");

    //Ignores the first line of the file
    char buffer = '\0';
    while(buffer != '\n' &&
          buffer != '\r' &&
          buffer != EOF) {
        buffer = fgetc(inFile);
    }
    if(buffer == '\r') {
        buffer = fgetc(inFile);
        if(buffer != '\n') {
            ungetc(buffer, inFile);
        }
    }

    //Writes the header
    fwrite("0", 1, 1, outFile);
    long int byteOffset = -1;
    fwrite(&byteOffset, 8, 1, outFile);
    fwrite(HEADER, 1, HEADER_SIZE, outFile);
    byteOffset = 0;
    fwrite(&byteOffset, 8, 1, outFile);
    int removed = 0;
    fwrite(&removed, 4, 1, outFile);

    //Adds the data to the file
    while(buffer != EOF) {

        struct data newRegister = readcsvline(inFile, &buffer);

        //Stops the loop if gets a into a empty line
        if(buffer == EOF) {
            break;
        }

        int size = getDataSize2(newRegister);
        addNewReg2(&newRegister, size, outFile);
        free(newRegister.city);
        free(newRegister.brand);
        free(newRegister.model);
    }

    //Writes the status of the file
    fseek(outFile, 0, SEEK_SET);
    fwrite("1", 1, 1, outFile);

    fclose(inFile);
    fclose(outFile);

    binarioNaTela(outputFileName);

    free(inputFileName);
    free(outputFileName);
}

//Executes the second command
void command2_2() {
    char* fileName = readstring(stdin, ' ');
    FILE* file = openFile(fileName, "r");
    testStatus(file);

    //Jumps the header
    fseek(file, 190, SEEK_SET);

    char buffer;
    int counter = 0;

    while(fread(&buffer, 1, 1, file) != 0) {
        ungetc(buffer, file);
        ++counter;

        struct data curData = getReg2(file, &buffer);
        if(buffer == '1') {
            break;
        }

        printData(curData);

        free(curData.city);
        free(curData.brand);
        free(curData.model);
    }

    if(counter == 0) {
        printf("Registro inexistente.\n");
    }
    free(fileName);
    fclose(file);
}

//Executes the third command
void command3_2() {
    char *fileName = readstring(stdin, ' ');
    FILE *file = openFile(fileName, "r");
    testStatus(file);

    //Jumps the header
    fseek(file, 190, SEEK_SET);

    int number;
    scanf("%d ", &number);

    //Saves all values to be compared in one struct
    struct data searchData = getData(number);

    char buffer;
    int counter = 0;
    while (fread(&buffer, 1, 1, file) != 0) {
        ungetc(buffer, file);

        struct data curData = getReg2(file, &buffer);
        if (buffer == '1') {
            break;
        }

        if(dataComp(searchData, curData) == '0') {
            printData(curData);
            ++counter;
        }

        free(curData.city);
        free(curData.brand);
        free(curData.model);
    }

    if(counter == 0){
        printf("Registro inexistente.\n");
    }

    free(searchData.city);
    free(searchData.brand);
    free(searchData.model);
    free(fileName);
    fclose(file);
}

//Gets the size of the register
int getDataSize2(struct data reg) {
    int registerSize = 22;
    if(strlen(reg.city) > 0) {
        registerSize += 5;
        registerSize += strlen(reg.city);
    }
    if(strlen(reg.brand) > 0) {
        registerSize += 5;
        registerSize += strlen(reg.brand);
    }
    if(strlen(reg.model) > 0) {
        registerSize += 5;
        registerSize += strlen(reg.model);
    }

    return registerSize;
}

//Reads the data from one register
struct data readBiData2(FILE* file, long int regSize) {
    struct data curData = newNullData();

    fread(&curData.id, 4, 1, file);
    fread(&curData.year, 4, 1, file);
    fread(&curData.qtt, 4, 1, file);
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

    regSize -= 22;

    int counter = 0;
    while(regSize > 4 && counter < 3) {
        buffer = '\0';
        if(fread(&buffer, 1, 1, file) == 0 || buffer == '$') {
            ungetc(buffer, file);
            break;
        }

        ungetc(buffer,file);
        ++counter;
        char code = counter;
        int size = 0;
        char* string = readBiString(file, &size, &code);
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

    fseek(file, regSize, SEEK_CUR);

    return curData;
}

//Creates a new register
void addNewReg2(struct data *newRegister, int regSize, FILE* file) {
    fseek(file, 0, SEEK_END);

    //Writes that the file isn't removed
    fwrite("0", 1, 1, file);

    //Writes the size of the register
    fwrite(&regSize, 4, 1, file);

    //Writes the byte offset of the next logically removed register
    long int byteOffset = -1;
    fwrite(&byteOffset, 8, 1, file);

    //Writes all the data
    writeBiData(*newRegister, file);

    //Updates the byte offset in the header
    long int nextByteOff = ftell(file);
    fseek(file, 178, SEEK_SET);
    fwrite(&nextByteOff, 8, 1, file);

    fseek(file, 0, SEEK_END);
}

//Ignores one register
void passReg2(FILE* file) {
    long int nextReg = 0;
    int nextRegBuffer;
    fread(&nextRegBuffer, 4, 1, file);
    nextReg += nextRegBuffer;
    fseek(file, nextReg, SEEK_CUR);

    if(nextReg < 0) {
        printf(ERROR_MSG);
        exit (EXIT_SUCCESS);
    }
}

//Places the file pointer at the beginning of non logically removed register
void findReg2(FILE* file, char* buffer) {
    *buffer = '1';
    while(fread(buffer, 1, 1, file) != 0 && *buffer == '1') {
        passReg2(file);
    }
}

//Returns the next non logically removed register
struct data getReg2(FILE* file, char* buffer) {
    struct data curData = newNullData();

    findReg2(file, buffer);

    if(*buffer == '0') {
        int nextRegBuffer = 0;
        fread(&nextRegBuffer, 4, 1, file);
        long int nextReg = nextRegBuffer;
        fseek(file, 8, SEEK_CUR);
        curData = readBiData2(file, nextReg);
    }
    else {
        curData.city = malloc(1);
        curData.city[0] = '\0';
        curData.brand = malloc(1);
        curData.brand[0] = '\0';
        curData.model = malloc(1);
        curData.model[0] = '\0';
    }

    return curData;
}