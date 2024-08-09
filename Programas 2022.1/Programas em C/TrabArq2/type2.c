// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all functions that only work for files of type 2

#include "type2.h"

//Chooses what command to execute
void type2(char command) {
    switch(command) {
        case '5':
            command5_2();
            break;

        case '6':
            command6_2();
            break;

        case '7':
            command7_2();
            break;

        case '8':
            command8_2();
            break;

        default:
            printf(ERROR_MSG);
    }
}

//Executes the fifth command (index)
void command5_2() {
    char* binFileName = readstring(stdin, ' ');
    char* indexFileName = readstring(stdin, ' ');

    FILE* binFile = openFile(binFileName, "rb");
    testStatus(binFile);

    //Jumps the header
    fseek(binFile, 190, SEEK_SET);

    //Creates the array of indexes
    struct indexArray2 indexArray;
    indexArray.size = 0;
    indexArray.indexes = malloc(0);

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

        //Adds a new value to the index array
        if(id != -1){
            addIndex2(id, offset, &indexArray);
        }
    }
    fclose(binFile);

    //Writes the indexes in the index file
    FILE* indexFile = openFile(indexFileName, "wb+");
    fwrite("0", 1, 1, indexFile);
    writeIndexes2(&indexArray, indexFile);
    free(indexArray.indexes);

    //Closes the index file
    fseek(indexFile, 0, SEEK_SET);
    fwrite("1", 1, 1, indexFile);
    fclose(indexFile);

    binarioNaTela(indexFileName);

    free(binFileName);
    free(indexFileName);
}

//Executes the sixth command (remove)
void command6_2() {
    char* binFileName = readstring(stdin, ' ');
    char* indexFileName = readstring(stdin, ' ');

    FILE* binFile = openFile(binFileName, "rb+");
    FILE* indexFile = openFile(indexFileName, "rb");

    testStatus(binFile);
    testStatus(indexFile);

    fwrite("0", 1, 1, binFile);

    //Copies the indexes from the file to an array
    fseek(indexFile, 1, SEEK_SET);
    struct indexArray2 indexArray = copyIndexes2(indexFile);
    fclose(indexFile);

    //Removes the registers
    int amount;
    scanf("%d ", &amount);
    for(int i = 0; i < amount; ++i){
        //Jumps the header
        fseek(binFile, 190, SEEK_SET);

        //Reads the number of parameters
        int number;
        scanf("%d ", &number);

        //Reads the parameters
        struct data searchData = getParData(number);

        //Finds the positions of the matching data in the index file
        if(searchData.id != -1 && searchData.id != -2){
            //Finds in which byte offset of the data file the index file points to
            long int position = searchPositionIndex2(searchData.id, &indexArray);

            //Checks if exists any register with the desired id
            if(position != -1){
                //Moves the file pointer to the position of the register that was found in the index file
                fseek(binFile, position, SEEK_SET);

                //Tests if its in the end of file and if the register is logically removed
                char buffer;
                if(fread(&buffer, 1, 1, binFile) != 0 && buffer == '0'){
                    //Reads the size of the register
                    int size;
                    fread(&size, 4, 1, binFile);

                    //Skips the next byte offset value
                    fseek(binFile, 8, SEEK_CUR);

                    //Compares if the values in the register are the same that the searched
                    struct data curData = readBiData2( (long int)size, binFile);
                    if(dataComp(searchData, curData) == '0'){
                        removeReg2(position, binFile);
                        removeIndex2(curData.id, &indexArray);
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
            struct positionsArray2 positions = searchData2(&searchData, binFile);

            //Deletes all the registers needed
            for(int j = 0; j < positions.size; ++j){
                removeReg2(positions.positions[j], binFile);
            }
            free(positions.positions);

            //Deletes all the ids needed
            for(int j = 0; j < positions.idAmount; ++j){
                removeIndex2(positions.ids[j], &indexArray);
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
    writeIndexes2(&indexArray, indexFile);
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

//Executes the seventh command (add)
void command7_2() {
    char* binFileName = readstring(stdin, ' ');
    char* indexFileName = readstring(stdin, ' ');

    FILE* binFile = openFile(binFileName, "rb+");
    FILE* indexFile = openFile(indexFileName, "rb");

    testStatus(binFile);
    testStatus(indexFile);

    fwrite("0", 1, 1, binFile);

    //Jumps the header
    fseek(binFile, 190, SEEK_SET);
    fseek(indexFile, 1, SEEK_SET);

    //Copies the indexes from the file to an array
    struct indexArray2 indexArray = copyIndexes2(indexFile);
    fclose(indexFile);

    //Adds the registers
    int amount;
    scanf("%d ", &amount);
    for(int i = 0; i < amount; ++i){
        struct data newRegister = readDataLine(stdin);

        //Searchs for a place to write the data in the file
        long int offset;
        saveReg2(&newRegister, &offset, binFile);

        //Updates the index array if needed
        if(newRegister.id != -1){
            addIndex2(newRegister.id, offset, &indexArray);
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
    writeIndexes2(&indexArray, indexFile);
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

//Executes the eighth command (change)
void command8_2() {
    char* binFileName = readstring(stdin, ' ');
    char* indexFileName = readstring(stdin, ' ');

    FILE* binFile = openFile(binFileName, "rb+");
    FILE* indexFile = openFile(indexFileName, "rb");

    testStatus(binFile);
    testStatus(indexFile);

    fwrite("0", 1, 1, binFile);

    //Copies the indexes from the file to an array
    fseek(indexFile, 1, SEEK_SET);
    struct indexArray2 indexArray = copyIndexes2(indexFile);
    fclose(indexFile);

    //Changes the registers
    int amount;
    scanf("%d ", &amount);
    for(int i = 0; i < amount; ++i){
        //Jumps the header
        fseek(binFile, 190, SEEK_SET);

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
            long int position = searchPositionIndex2(searchData.id, &indexArray);

            //Checks if exists any register with the desired id
            if(position != -1){
                //Moves the file pointer to the position of the register that was found in the index file
                fseek(binFile, position, SEEK_SET);

                //Tests if its in the end of file and if the register is logically removed
                char buffer;
                if(fread(&buffer, 1, 1, binFile) != 0 && buffer == '0'){
                    //Reads the size of the register
                    int size;
                    fread(&size, 4, 1, binFile);

                    //Skips the next logically removed register's byte offset
                    fseek(binFile, 8, SEEK_CUR);

                    //Reads the data from the register found
                    struct data curData = readBiData2( (long int)size, binFile);

                    //Compares if the values in the register are the same that the searched
                    if(dataComp(searchData, curData) == '0'){
                        //Moves the file pointer to the position of the register the will be changed
                        long int offset = position + 1;

                        //Creates a struct containing all the final values to be placed in the register
                        struct data newData = changeData(&curData, &changedData);
                        int newDataSize = getDataSize2(newData);

                        //Tests if is possible to just update the register
                        if(size < newDataSize){
                            removeReg2(position, binFile);
                            saveReg2(&newData, &position, binFile);
                        }

                        //Reuses the same register if possible
                        else{
                            fseek(binFile, offset + 12, SEEK_SET);
                            reuseReg2(&newData, newDataSize, size, binFile);
                        }

                        //Updates the index array
                        changeIndex2(curData.id, newData.id, position, &indexArray);
                    }

                    freeData(&curData);
                }
            }
        }

        //Searchs for the registers if they don't have indexes
        else{
            //Creates a array with the positions of all matching registers with the search data
            struct positionsArray2 positions = searchData2(&searchData, binFile);

            //Changes all the registers needed
            for(int j = 0; j < positions.size; ++j){
                //Moves the file pointer to the position of the register that will be changed
                long int offset = positions.positions[j];
                fseek(binFile, offset + 1, SEEK_SET);

                //Reads the size of the register
                int size;
                fread(&size, 4, 1, binFile);

                //Read the data present in the register
                fseek(binFile, 8, SEEK_CUR);
                struct data curData = readBiData2((long int)size, binFile);

                //Creates a struct containing all the final values to be placed in the register
                struct data newData = changeData(&curData, &changedData);
                int newDataSize = getDataSize2(newData);

                //Tests if is possible to just update the register
                if(size < newDataSize){
                    removeReg2(offset, binFile);
                    saveReg2(&newData, &offset, binFile);
                }

                //Reuses the same register if possible
                else{
                    fseek(binFile, offset + 13, SEEK_SET);
                    reuseReg2(&newData, newDataSize, size, binFile);
                }

                //Updates the index array
                changeIndex2(curData.id, newData.id, offset, &indexArray);
                freeData(&curData);
            }
            free(positions.positions);
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
    writeIndexes2(&indexArray, indexFile);
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

//Searchs for all the byte offsets of the corresponding datas
struct positionsArray2 searchData2(struct data *searchData, FILE* binFile){
    //Allocs memory for the positions of the removed registers
    struct positionsArray2 positionsArray;
    positionsArray.size = 0;
    positionsArray.positions = malloc(0);
    positionsArray.idAmount = 0;
    positionsArray.ids = malloc(0);

    //Searchs in all register to find the positions of the registers that where searched
    char buffer;
    while (fread(&buffer, 1, 1, binFile) != 0) {
        fseek(binFile, -1, SEEK_CUR);

        //Finds a non logically removed register
        findReg2(&buffer, binFile);
        long int offset = ftell(binFile) - 1;

        //Reads the current register
        fseek(binFile, -1, SEEK_CUR);
        struct data curData = getReg2(&buffer, binFile);
        if (buffer == '1') {
            freeData(&curData);
            break;
        }

        //Checks if the register found has all parameters
        if(dataComp(*searchData, curData) == '0') {
            ++positionsArray.size;
            int size = positionsArray.size;
            positionsArray.positions = realloc(positionsArray.positions, size * sizeof(long int));
            positionsArray.positions[size - 1] = offset;

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

//Removes one register
void removeReg2(long int offset, FILE *binFile) {
    //Moves the file pointer to the byte offset of the register to be removed
    fseek(binFile, offset, SEEK_SET);

    //Logically removes the register
    fwrite("1", 1, 1, binFile);

    //Reads the register size
    int regSize;
    fread(&regSize, 4, 1, binFile);

    //Skips the next logically removed register's byte offset
    fseek(binFile, 8, SEEK_CUR);

    //Reads the top of the list of logically removed registers
    fseek(binFile, 1, SEEK_SET);
    long int top;
    fread(&top, 8, 1, binFile);

    //Buffers
    long int nextReg = top;
    long int lastReg = 0;
    long int curReg = 0;

    //Search for where to place the register in the logically removed pile
    int curRegSize;
    while(nextReg != -1){
        //Updates the buffers
        lastReg = curReg;
        curReg = nextReg;

        //Moves to the next register
        fseek(binFile, nextReg + 1, SEEK_SET);

        //Reads the size of the current register
        fread(&curRegSize, 4, 1, binFile);

        //If finds somewhere to place the register, stops the loop
        if(curRegSize <= regSize){
            break;
        }

        //Reads the position of the next removed register
        fread(&nextReg, 8, 1, binFile);
    }
    if(nextReg == -1){
        lastReg = curReg;
        curReg = -1;
    }

    //Writes the position of the removed register in the previos removed register
    if(lastReg == 0){
        fseek(binFile, 1, SEEK_SET);
    }
    else{
        fseek(binFile, lastReg + 5, SEEK_SET);
    }
    fwrite(&offset, 8, 1, binFile);

    //Writes the position of the next removed register in the removed register
    fseek(binFile, offset + 5, SEEK_SET);
    fwrite(&curReg, 8, 1, binFile);

    //Reads the number of removed registers
    fseek(binFile, 186, SEEK_SET);
    int removed;
    fread(&removed, 4, 1, binFile);

    //Increases the number of removed registers
    fseek(binFile, 186, SEEK_SET);
    ++removed;
    fwrite(&removed, 4, 1, binFile);
}