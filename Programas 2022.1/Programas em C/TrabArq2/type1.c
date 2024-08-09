// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all functions that only work for files of type 1

#include "type1.h"

//Chooses what command to execute
void type1(char command) {
    switch(command) {
        case '5':
            command5_1();
            break;

        case '6':
            command6_1();
            break;

        case '7':
            command7_1();
            break;

        case '8':
            command8_1();
            break;

        default:
            printf(ERROR_MSG);
    }
}

//Executes the fifth command
void command5_1() {
    char* binFileName = readstring(stdin, ' ');
    char* indexFileName = readstring(stdin, ' ');

    FILE* binFile = openFile(binFileName, "rb");
    testStatus(binFile);

    //Jumps the header
    fseek(binFile, 182, SEEK_SET);

    //Creates the array of indexes
    struct indexArray1 indexArray;
    indexArray.size = 0;
    indexArray.indexes = malloc(0);

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

        //Adds a new value to the index array
        if(id != -1){
            addIndex1(id, (offset - 182) / REG_SIZE, &indexArray);
        }
    }
    fclose(binFile);

    //Writes the indexes in the index file
    FILE* indexFile = openFile(indexFileName, "wb+");
    fwrite("0", 1, 1, indexFile);
    writeIndexes1(&indexArray, indexFile);
    free(indexArray.indexes);

    //Closes the index file
    fseek(indexFile, 0, SEEK_SET);
    fwrite("1", 1, 1, indexFile);
    fclose(indexFile);

    binarioNaTela(indexFileName);

    free(binFileName);
    free(indexFileName);
}

//Executes the sixth command
void command6_1() {
    char* binFileName = readstring(stdin, ' ');
    char* indexFileName = readstring(stdin, ' ');

    FILE* binFile = openFile(binFileName, "rb+");
    FILE* indexFile = openFile(indexFileName, "rb");

    testStatus(binFile);
    testStatus(indexFile);

    fwrite("0", 1, 1, binFile);

    //Copies the indexes from the file to an array
    fseek(indexFile, 1, SEEK_SET);
    struct indexArray1 indexArray = copyIndexes1(indexFile);
    fclose(indexFile);

    //Removes the registers
    int amount;
    scanf("%d ", &amount);
    for(int i = 0; i < amount; ++i){
        //Jumps the header
        fseek(binFile, 182, SEEK_SET);

        //Reads the number of parameters
        int number;
        scanf("%d ", &number);

        //Reads the parameters
        struct data searchData = getParData(number);

        //Finds the positions of the matching data in the index file
        if(searchData.id != -1 && searchData.id != -2){
            //Finds in which byte offset of the data file the index file points to
            int rrn = searchRRNIndex1(searchData.id, &indexArray);

            //Checks if exists any register with the desired id
            if(rrn != -1){
                //Moves the file pointer to the position of the register that was found in the index file
                fseek(binFile, 182 + (rrn * REG_SIZE), SEEK_SET);

                //Tests if its in the end of file and if the register is logically removed
                char buffer;
                if(fread(&buffer, 1, 1, binFile) != 0 && buffer == '0'){
                    //Skips the next rrn value
                    fseek(binFile, 4, SEEK_CUR);

                    //Compares if the values in the register are the same that the searched
                    struct data curData = readBiData1(binFile);
                    if(dataComp(searchData, curData) == '0'){
                        removeReg1(rrn, binFile);
                        removeIndex1(curData.id, &indexArray);
                    }
                    freeData(&curData);
                }
                else{
                    printf("Arquivo de índices guarda a posição de um registro inexistente.\n");
                }
            }
        }

        //Searchs for the registers if they don't have indexes
        else{
            //Creates a array with the positions of all matching registers with the search data
            struct positionsArray1 positions = searchData1(&searchData, binFile);

            //Deletes all the registers needed
            for(int j = 0; j < positions.size; ++j){
                removeReg1(positions.rrns[j], binFile);
            }
            free(positions.rrns);

            //Deletes all the ids needed
            for(int j = 0; j < positions.idAmount; ++j){
                removeIndex1(positions.ids[j], &indexArray);
            }
            free(positions.ids);
        }
        freeData(&searchData);
    }

    //Closes the binary file
    fseek(binFile, 0, SEEK_SET);
    fwrite("1", 1, 1, binFile);
    fclose(binFile);

    //Rewrites the index file
    indexFile = openFile(indexFileName, "wb+");
    fwrite("0", 1, 1, indexFile);
    writeIndexes1(&indexArray, indexFile);
    free(indexArray.indexes);

    //Closes the index file
    fseek(indexFile, 0, SEEK_SET);
    fwrite("1", 1, 1, indexFile);
    fclose(indexFile);

    binarioNaTela(binFileName);
    binarioNaTela(indexFileName);

    free(binFileName);
    free(indexFileName);
}

//Executes the seventh command
void command7_1() {
    char* binFileName = readstring(stdin, ' ');
    char* indexFileName = readstring(stdin, ' ');

    FILE* binFile = openFile(binFileName, "rb+");
    FILE* indexFile = openFile(indexFileName, "rb");

    testStatus(binFile);
    testStatus(indexFile);

    fwrite("0", 1, 1, binFile);

    //Jumps the header
    fseek(binFile, 182, SEEK_SET);
    fseek(indexFile, 1, SEEK_SET);

    //Copies the indexes from the file to an array
    struct indexArray1 indexArray = copyIndexes1(indexFile);
    fclose(indexFile);

    //Adds the registers
    int amount;
    scanf("%d ", &amount);
    for(int i = 0; i < amount; ++i){
        struct data newRegister = readDataLine(stdin);

        //Searchs for a place to write the data in the file
        int rrn;
        saveReg1(&newRegister, &rrn, binFile);

        //Updates the index array if needed
        if(newRegister.id != -1){
            addIndex1(newRegister.id, rrn, &indexArray);
        }

        freeData(&newRegister);
    }

    //Closes the binary file
    fseek(binFile, 0, SEEK_SET);
    fwrite("1", 1, 1, binFile);
    fclose(binFile);

    //Rewrites the index file
    indexFile = openFile(indexFileName, "wb+");
    fwrite("0", 1, 1, indexFile);
    writeIndexes1(&indexArray, indexFile);
    free(indexArray.indexes);

    //Closes the index file
    fseek(indexFile, 0, SEEK_SET);
    fwrite("1", 1, 1, indexFile);
    fclose(indexFile);

    binarioNaTela(binFileName);
    binarioNaTela(indexFileName);

    free(binFileName);
    free(indexFileName);
}

//Executes the eighth command
void command8_1() {
    char* binFileName = readstring(stdin, ' ');
    char* indexFileName = readstring(stdin, ' ');

    FILE* binFile = openFile(binFileName, "rb+");
    FILE* indexFile = openFile(indexFileName, "rb");

    testStatus(binFile);
    testStatus(indexFile);

    fwrite("0", 1, 1, binFile);

    //Copies the indexes from the file to an array
    fseek(indexFile, 1, SEEK_SET);
    struct indexArray1 indexArray = copyIndexes1(indexFile);
    fclose(indexFile);

    //Changes the registers
    int amount;
    scanf("%d ", &amount);
    for(int i = 0; i < amount; ++i){
        //Jumps the header
        fseek(binFile, 182, SEEK_SET);

        //Reads all the values to search the registers that will be changed
        int parameters;
        scanf("%d ", &parameters);
        struct data searchData = getParData(parameters);

        //Reads all the new values and place then in a struct
        int changes;
        scanf("%d ", &changes);
        struct data changedData = getParData(changes);

        //Finds the positions of the matching data in the index file
        if(searchData.id != -1 && searchData.id != -2){
            int rrn = searchRRNIndex1(searchData.id, &indexArray);

            //Checks if exists any register with the desired id
            if(rrn != -1){
                //Moves the file pointer to the position of the register that was found in the index file
                fseek(binFile, 182 + (rrn * REG_SIZE), SEEK_SET);

                //Tests if its in the end of file and if the register is logically removed
                char buffer;
                if(fread(&buffer, 1, 1, binFile) != 0 && buffer == '0'){
                    //Moves the file pointer to the position of the data
                    fseek(binFile, 4, SEEK_CUR);

                    //Reads the data from the register found
                    struct data curData = readBiData1(binFile);

                    //Compares if the values in the register are the same that the searched
                    if(dataComp(searchData, curData) == '0'){
                        //Creates a struct containing all the final values to be placed in the register
                        struct data newData = changeData(&curData, &changedData);

                        //Reuses the register
                        fseek(binFile, 187 + (rrn * REG_SIZE), SEEK_SET);
                        reuseReg1(&newData, getDataSize1(newData), binFile);

                        //Updates the index array
                        changeIndex1(curData.id, newData.id, rrn, &indexArray);
                    }
                    freeData(&curData);
                }
            }
        }

        //Searchs for the registers if they don't have indexes
        else{
            //Creates a array with the positions of all matching registers with the search data
            struct positionsArray1 positions = searchData1(&searchData, binFile);

            //Changes all the registers needed
            for(int j = 0; j < positions.size; ++j){
                //Moves the file pointer to the position of the register that will be changed
                int rrn = positions.rrns[j];
                fseek(binFile, 187 + (rrn * REG_SIZE), SEEK_SET);

                //Read the data present in the register
                struct data curData = readBiData1(binFile);

                //Creates a struct containing all the final values to be placed in the register
                struct data newData = changeData(&curData, &changedData);

                //Reuses the register
                fseek(binFile, 187 + (rrn * REG_SIZE), SEEK_SET);
                reuseReg1(&newData, getDataSize1(newData), binFile);

                //Updates the index array
                changeIndex1(curData.id, newData.id, rrn, &indexArray);
                freeData(&curData);
            }
            free(positions.rrns);
        }
        freeData(&searchData);
        freeData(&changedData);
    }

    //Closes the binary file
    fseek(binFile, 0, SEEK_SET);
    fwrite("1", 1, 1, binFile);
    fclose(binFile);

    //Rewrites the index file
    indexFile = openFile(indexFileName, "wb+");
    fwrite("0", 1, 1, indexFile);
    writeIndexes1(&indexArray, indexFile);
    free(indexArray.indexes);

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

//Searchs for all the rrns of the corresponding datas
struct positionsArray1 searchData1(struct data *searchData, FILE* binFile){
    //Allocs memory for the positions of the removed registers
    struct positionsArray1 positionsArray;
    positionsArray.size = 0;
    positionsArray.rrns = malloc(0);
    positionsArray.idAmount = 0;
    positionsArray.ids = malloc(0);

    //Searchs in all register to find the positions of the registers that where searched
    char buffer;
    while (fread(&buffer, 1, 1, binFile) != 0) {
        fseek(binFile, -1, SEEK_CUR);

        //Finds a non logically removed register
        findReg1(&buffer, binFile);
        long int offset = ftell(binFile) - 1;
        int rrn = (offset - 182) / REG_SIZE;

        //Reads the current register
        fseek(binFile, -1, SEEK_CUR);
        struct data curData = getReg1(&buffer, binFile);
        if (buffer == '1') {
            freeData(&curData);
            break;
        }

        //Checks if the register found has all parameters
        if(dataComp(*searchData, curData) == '0') {
            ++positionsArray.size;
            int size = positionsArray.size;
            positionsArray.rrns = realloc(positionsArray.rrns, size * sizeof(int));
            positionsArray.rrns[size - 1] = rrn;

            if(curData.id != -1){
                ++positionsArray.idAmount;
                positionsArray.ids = realloc(positionsArray.ids, positionsArray.idAmount * sizeof(int));
                positionsArray.ids[positionsArray.idAmount - 1] = curData.id;
            }
        }

        freeData(&curData);
    }

    return positionsArray;
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

//Removes one register
void removeReg1(int rrn, FILE *binFile) {
    //Reads the top of the list of logically removed registers
    fseek(binFile, 1, SEEK_SET);
    int top;
    fread(&top, 4, 1, binFile);

    //Writes the position of the removed register in the top
    fseek(binFile, 1, SEEK_SET);
    fwrite(&rrn, 4, 1, binFile);

    //Moves the file pointer to the byte offset of the register to be removed
    fseek(binFile, 182 + (rrn * REG_SIZE), SEEK_SET);

    //Logically removes the register
    fwrite("1", 1, 1, binFile);

    //Writes the position of the next removed register in the removed register
    fwrite(&top, 4, 1, binFile);

    //Reads the number of removed registers
    fseek(binFile, 178, SEEK_SET);
    int removed;
    fread(&removed, 4, 1, binFile);

    //Increases the number of removed registers
    fseek(binFile, 178, SEEK_SET);
    ++removed;
    fwrite(&removed, 4, 1, binFile);
}