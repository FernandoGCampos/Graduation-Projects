// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all functions that only work for files of type 1

#include "type1.h"

//Chooses what command to execute
void type1(int command) {
    switch(command) {
        case 9:
            command9_1();
            break;

        case 10:
            command10_1();
            break;

        case 11:
            command11_1();
            break;

        default:
            printf(ERROR_MSG);
    }
}

//Executes the fifth command
void command9_1() {
    char* binFileName = readstring(stdin, ' ');
    char* indexFileName = readstring(stdin, ' ');

    FILE* binFile = openFile(binFileName, "rb");
    testStatus(binFile);

    //Jumps the header
    fseek(binFile, 182, SEEK_SET);

    //Creates the index file
    FILE* indexFile = openFile(indexFileName, "wb+");
    fwrite("0", 1, 1, indexFile);
    int intBuffer = -1;
    fwrite(&intBuffer, 4, 1, indexFile);
    intBuffer = 0;
    fwrite(&intBuffer, 4, 1, indexFile);
    intBuffer = 0;
    fwrite(&intBuffer, 4, 1, indexFile);
    for(int i = 13; i < NODE1_SIZE; ++i){
        fwrite("$", 1, 1, indexFile);
    }

    //Reads the binary file until finds the end of file
    char buffer;
    while(fread(&buffer, 1, 1, binFile) != 0) {
        fseek(binFile, -1, SEEK_CUR);

        //Finds the next not logically removed register
        findReg1(&buffer, binFile);
        if(buffer == '1') {
            break;
        }

        //Saves the byte offset of the register
        long int offset = ftell(binFile) - 1;

        //Skips the "next logically removed register" value
        fseek(binFile, 4, SEEK_CUR);

        //Read the id
        int id;
        fread(&id, 4, 1, binFile);

        //Skips the rest of the register
        fseek(binFile, REG_SIZE - 9, SEEK_CUR);

        //Adds a new value to the index file
        if(id != -1){
            addIndex1(id, (offset - 182) / REG_SIZE, indexFile);
        }
    }
    fclose(binFile);

    //Closes the index file
    fseek(indexFile, 0, SEEK_SET);
    fwrite("1", 1, 1, indexFile);
    fclose(indexFile);

    binarioNaTela(indexFileName);

    free(binFileName);
    free(indexFileName);
}

//Executes the sixth command
void command10_1() {
    char* binFileName = readstring(stdin, ' ');
    char* indexFileName = readstring(stdin, ' ');

    FILE* binFile = openFile(binFileName, "rb");
    FILE* indexFile = openFile(indexFileName, "rb");

    testStatus(binFile);
    testStatus(indexFile);

    //Reads the ID
    int id;
    scanf("id %d ", &id);

    //Searches for the position in the data file using the index file
    int rrn = searchRRNIndex1(id, indexFile);

    //If is unable to find a register, then it informs the user
    if(rrn == -1){
        printf("Registro inexistente.\n");
    }

    //Prints the register
    else{
        fseek(binFile, (rrn * REG_SIZE) + 187, SEEK_SET);

        //Reads the data from the register
        struct data reg = readBiData1(binFile);

        //Prints the register
        printData(reg);
        freeData(&reg);
    }

    //Closes the files
    fclose(binFile);
    fclose(indexFile);
    free(binFileName);
    free(indexFileName);
}

//Executes the seventh command
void command11_1() {
    char* binFileName = readstring(stdin, ' ');
    char* indexFileName = readstring(stdin, ' ');

    FILE* binFile = openFile(binFileName, "rb+");
    FILE* indexFile = openFile(indexFileName, "rb+");

    testStatus(binFile);
    testStatus(indexFile);

    //Adds the registers
    int amount;
    scanf("%d ", &amount);
    for(int i = 0; i < amount; ++i){
        struct data newRegister = readDataLine(stdin);

        //Searchs for a place to write the data in the file
        int rrn;
        saveReg1(&newRegister, &rrn, binFile);

        //Updates the index file if needed
        if(newRegister.id != -1){
            addIndex1(newRegister.id, rrn, indexFile);
        }

        freeData(&newRegister);
    }

    //Closes the binary file
    fseek(binFile, 0, SEEK_SET);
    fwrite("1", 1, 1, binFile);
    fclose(binFile);

    //Closes the index file
    fseek(indexFile, 0, SEEK_SET);
    fwrite("1", 1, 1, indexFile);
    fclose(indexFile);

    binarioNaTela(binFileName);
    binarioNaTela(indexFileName);

    free(binFileName);
    free(indexFileName);
}

//Gets the size of the register
int getDataSize1(struct data reg) {
    int registerSize = 19;
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
struct data readBiData1(FILE* file) {
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

    int dataSize = REG_SIZE;
    dataSize -= 19;

    int counter = 0;
    while(dataSize > 4 && counter < 3) {
        buffer = '\0';
        if(fread(&buffer, 1, 1, file) == 0 || buffer == '$') {
            ungetc(buffer, file);
            break;
        }

        ungetc(buffer,file);
        ++counter;
        char code = counter;
        int size = 0;
        char* string = readBiString(&code, &size, file);
        if(size > 0) {
            dataSize -= 5;
            dataSize -= size;
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

    fseek(file, dataSize, SEEK_CUR);

    return curData;
}

//Creates a new register
void addNewReg1(struct data *newRegister, FILE* file) {
    fseek(file, 0, SEEK_END);

    //Writes that the file isn't removed
    fwrite("0", 1, 1, file);

    //Writes the next logically removed register
    int removed = -1;
    fwrite(&removed, 4, 1, file);

    //Writes all the data
    writeBiData(*newRegister, file);

    //Writes all null values
    for(int i = REG_SIZE - getDataSize1(*newRegister); i > 0; --i){
        fwrite("$", 1, 1, file);
    }

    //Updates the next RRN marker in the header
    int nextRrn = 0;
    fseek(file, 174, SEEK_SET);
    fread(&nextRrn, 4, 1, file);

    fseek(file, 174, SEEK_SET);
    nextRrn += 1;
    fwrite(&nextRrn, 4, 1, file);

    fseek(file, 0, SEEK_END);
}

//Places the file pointer at the beginning of non logically removed register
void findReg1(char *buffer, FILE *file) {
    *buffer = '1';
    while(fread(buffer, 1, 1, file) != 0 && *buffer == '1') {
        fseek(file, REG_SIZE - 1, SEEK_CUR);
    }
}

//Returns the next non logically removed register
struct data getReg1(char *buffer, FILE *file) {
    struct data curData = newNullData();

    findReg1(buffer, file);

    if(*buffer == '0') {
        fseek(file, 4, SEEK_CUR);
        curData = readBiData1(file);
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

//Reuses a logically deleted register
void reuseReg1(struct data *newRegister, int dataSize, FILE* file) {
    //Writes all the data
    writeBiData(*newRegister, file);

    //Writes all the null values
    for(int i = dataSize; i < REG_SIZE; ++i) {
        fwrite("$", 1, 1, file);
    }
}

//Saves the data in a register
void saveReg1(struct data *newRegister, int *rrn, FILE *file) {
    //Reads the top of the file
    fseek(file, 1, SEEK_SET);
    int top;
    fread(&top, 4, 1, file);

    if(top == -1) {
        //Creates a new register
        fseek(file, 0, SEEK_END);
        long int offset = ftell(file);
        *rrn = (offset - 182) / REG_SIZE;
        addNewReg1(newRegister, file);
    }
    else {
        //Moves the file pointer to the position of the biggest logically removed register
        fseek(file, 183 + (top * REG_SIZE), SEEK_SET);

        //Saves the values of the positions off registers
        *rrn = top;
        int nextReg;

        //Reads the next removed register and places the new data
        fread(&nextReg, 4, 1, file);
        reuseReg1(newRegister, getDataSize1(*newRegister), file);

        //Writes the next removed register in the top
        fseek(file, 1, SEEK_SET);
        fwrite(&nextReg, 4, 1, file);

        //Removes the status of logically removed
        fseek(file, 182 + (top * REG_SIZE), SEEK_SET);
        char status = '0';
        fwrite(&status, 1, 1, file);

        //Removes the next logically removed register's byte offset
        int nextRRN = -1;
        fwrite(&nextRRN, 4, 1, file);

        //Reads the number of removed registers
        fseek(file, 178, SEEK_SET);
        int removed;
        fread(&removed, 4, 1, file);

        //Decreases the number of removed registers
        fseek(file, 178, SEEK_SET);
        --removed;
        fwrite(&removed, 4, 1, file);
    }
}