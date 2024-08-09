// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all functions that only work for files of type 2

#include "type2.h"

//Chooses what command to execute
void type2(int command) {
    switch(command) {
        case 9:
            command9_2();
            break;

        case 10:
            command10_2();
            break;

        case 11:
            command11_2();
            break;

        default:
            printf(ERROR_MSG);
    }
}

//Executes the fifth command
void command9_2() {
    char* binFileName = readstring(stdin, ' ');
    char* indexFileName = readstring(stdin, ' ');

    FILE* binFile = openFile(binFileName, "rb");
    testStatus(binFile);

    //Jumps the header
    fseek(binFile, 190, SEEK_SET);

    //Opens the index file
    FILE* indexFile = openFile(indexFileName, "wb+");
    fwrite("0", 1, 1, indexFile);
    int intBuffer = -1;
    fwrite(&intBuffer, 4, 1, indexFile);
    intBuffer = 0;
    fwrite(&intBuffer, 4, 1, indexFile);
    intBuffer = 0;
    fwrite(&intBuffer, 4, 1, indexFile);
    for(int i = 13; i < NODE2_SIZE; ++i){
        fwrite("$", 1, 1, indexFile);
    }

    //Reads the binary file until finds the end of file
    char buffer;
    while(fread(&buffer, 1, 1, binFile) != 0) {
        fseek(binFile, -1, SEEK_CUR);

        //Finds the next not logically removed register
        findReg2(&buffer, binFile);
        if(buffer == '1') {
            break;
        }

        //Saves the byte offset of the register
        long int offset = ftell(binFile) - 1;

        //Reads the size of the register
        int regSize;
        fread(&regSize, 4, 1, binFile);

        //Skips the "next logically removed register" value
        fseek(binFile, 8, SEEK_CUR);

        //Read the id
        int id;
        fread(&id, 4, 1, binFile);

        //Skips the rest of the register
        fseek(binFile, regSize - 12, SEEK_CUR);

        //Adds a new value to the index file
        if(id != -1){
            addIndex2(id, offset, indexFile);
        }
    }
    fclose(binFile);

    //Closes the index file
    fseek(indexFile, 0, SEEK_SET);
    fwrite("1", 1, 1, indexFile);
    fclose(indexFile);

    binarioNaTela(indexFileName);
    convertsIndexFile2(indexFileName);
    free(binFileName);
    free(indexFileName);
}

//Executes the sixth command
void command10_2() {
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
    long int pos = searchPositionIndex2(id, indexFile);

    //If is unable to find a register, then it informs the user
    if(pos == -1){
        printf("Registro inexistente.\n");
    }

    //Prints the register
    else{
        fseek(binFile, pos + 1, SEEK_SET);

        //REads the register size
        int buffer;
        fread(&buffer, 4, 1, binFile);
        fseek(binFile, 8, SEEK_CUR);
        long int regSize = buffer;

        //Reads the data from the register
        struct data reg = readBiData2(regSize, binFile);

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
void command11_2() {
    char* binFileName = readstring(stdin, ' ');
    char* indexFileName = readstring(stdin, ' ');

    FILE* binFile = openFile(binFileName, "rb+");
    FILE* indexFile = openFile(indexFileName, "rb+");

    testStatus(binFile);
    testStatus(indexFile);

    fwrite("0", 1, 1, binFile);
    fwrite("0", 1, 1, indexFile);

    //Adds the registers
    int amount;
    scanf("%d ", &amount);
    for(int i = 0; i < amount; ++i){
        struct data newRegister = readDataLine(stdin);

        //Searchs for a place to write the data in the file
        long int offset;
        saveReg2(&newRegister, &offset, binFile);

        //Updates the index file if needed
        if(newRegister.id != -1){
            addIndex2(newRegister.id, offset, indexFile);
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
struct data readBiData2(long int regSize, FILE *file) {
    struct data curData = newNullData();

    //Reads the fix size values
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

    //Updates the amount of bytes left in the register
    regSize -= 22;

    //Reads the variable size values
    int counter = 0;
    while(regSize > 4 && counter < 3) {
        buffer = '\0';
        if(fread(&buffer, 1, 1, file) == 0) {
            break;
        }
        else if(buffer == '$'){
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
    //Reads the size of the registere
    long int nextReg = 0;
    int nextRegBuffer;
    fread(&nextRegBuffer, 4, 1, file);
    nextReg += nextRegBuffer;

    //If the register have negative value, the program exits
    if(nextReg < 0) {
        printf(ERROR_MSG);
        exit (EXIT_SUCCESS);
    }

    //Seeks to the first byte after the register
    fseek(file, nextReg, SEEK_CUR);
}

//Places the file pointer at the beginning of non logically removed register
void findReg2(char *buffer, FILE *file) {
    *buffer = 1;
    while(fread(buffer, 1, 1, file) != 0 && *buffer == '1') {
        passReg2(file);
    }
}

//Returns the next non logically removed register
struct data getReg2(char *buffer, FILE *file) {
    struct data curData = newNullData();

    //Finds the next not logically removed register
    findReg2(buffer, file);

    if(*buffer == '0') {
        //Reads the size of the register
        int nextRegBuffer = 0;
        fread(&nextRegBuffer, 4, 1, file);
        long int nextReg = 0;
        nextReg += nextRegBuffer;

        //Skips the offset of the next logically removed register, because it's unnecessary
        fseek(file, 8, SEEK_CUR);
        curData = readBiData2(nextReg, file);
    }

    //If reaches the end of file and is unable to find a register
    //Allocates memory for the strings (avoids the problem of "double-freeing" memory)
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
void reuseReg2(struct data *newRegister, int regSize, int maxSize, FILE* file) {
    //Writes all the data
    writeBiData(*newRegister, file);

    //Writes all the null values
    for(int i = regSize; i < maxSize; ++i) {
        fwrite("$", 1, 1, file);
    }
}

//Saves the data in a register
void saveReg2(struct data *newRegister, long int *offset, FILE *file) {
    //Reads the top of the file
    fseek(file, 1, SEEK_SET);
    long int top;
    fread(&top, 8, 1, file);

    int regSize = getDataSize2(*newRegister);

    if(top == -1) {
        //Creates a new register
        fseek(file, 0, SEEK_END);
        *offset = ftell(file);
        addNewReg2(newRegister, regSize, file);
    }
    else {
        //Moves the file pointer to the position of the biggest logically removed register
        fseek(file, top + 1, SEEK_SET);

        //Reads the size of the logically removed register
        int size = 0;
        fread(&size, 4, 1, file);

        //Test if the new register fits in the current logically removed register
        if(size < regSize) {
            //Creates a new register
            fseek(file, 0, SEEK_END);
            *offset = ftell(file);
            addNewReg2(newRegister, regSize, file);
        }
        else {
            //Saves the values of the positions off registers
            *offset = top;
            long int curReg = top;
            long int nextReg;

            //Reads the next removed register and places the new data
            fread(&nextReg, 8, 1, file);
            reuseReg2(newRegister, regSize, size, file);

            //Writes the next removed register in the previous removed register
            fseek(file, 1, SEEK_SET);
            fwrite(&nextReg, 8, 1, file);

            //Removes the status of logically removed
            fseek(file, curReg, SEEK_SET);
            char status = '0';
            fwrite(&status, 1, 1, file);

            //Removes the next logically removed register's byte offset
            fseek(file, 4, SEEK_CUR);
            long int nextOffset = -1;
            fwrite(&nextOffset, 8, 1, file);

            //Reads the number of removed registers
            fseek(file, 186, SEEK_SET);
            int removed;
            fread(&removed, 4, 1, file);

            //Decreases the number of removed registers
            fseek(file, 186, SEEK_SET);
            --removed;
            fwrite(&removed, 4, 1, file);
        }
    }
}