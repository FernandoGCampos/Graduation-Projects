// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all universal data related functions

#include "data.h"
#include "extralib.h"

//Returns a struct with "null" values
struct data newNullData() {
    struct data nullData;

    nullData.id = -1;
    nullData.year = -1;
    nullData.qtt = -1;
    nullData.initials[0] = '\0';
    nullData.initials[1] = '\0';
    nullData.initials[2] = '\0';
    nullData.city = NULL;
    nullData.brand = NULL;
    nullData.model = NULL;

    return nullData;
}

//Reads one string in the binary file
char *readBiString(char *code, int *size, FILE *file) {
    int buffer;
    fread(&buffer, 4, 1, file);

    *size = buffer;
    fread(code, 1, 1, file);

    char* string = malloc(buffer + 1);
    fread(&*string, 1, buffer, file);
    string[buffer] = '\0';

    return string;
}

//Writes the data from the struct
void writeBiData(struct data newRegister, FILE* file) {
    //Writes the integers
    fwrite(&newRegister.id, 4, 1, file);
    fwrite(&newRegister.year, 4, 1, file);
    fwrite(&newRegister.qtt, 4, 1, file);

    //Writes the initials
    if(newRegister.initials[0] == '\0') {
        fwrite("$", 1, 1, file);
    }
    else {
        fwrite(&newRegister.initials[0], 1, 1, file);
    }
    if(newRegister.initials[1] == '\0') {
        fwrite("$", 1, 1, file);
    }
    else {
        fwrite(&newRegister.initials[1], 1, 1, file);
    }

    //Write the city related data
    int sizeBuffer = strlen(newRegister.city);
    if(sizeBuffer > 0) {
        fwrite(&sizeBuffer, 4, 1, file);
        fwrite("0", 1, 1, file);
        fwrite(newRegister.city, 1, sizeBuffer, file);
    }

    //Write the brand related data
    sizeBuffer = strlen(newRegister.brand);
    if(sizeBuffer > 0) {
        fwrite(&sizeBuffer, 4, 1, file);
        fwrite("1", 1, 1, file);
        fwrite(newRegister.brand, 1, sizeBuffer, file);
    }

    //Write the model related data
    sizeBuffer = strlen(newRegister.model);
    if(sizeBuffer > 0) {
        fwrite(&sizeBuffer, 4, 1, file);
        fwrite("2", 1, 1, file);
        fwrite(newRegister.model, 1, sizeBuffer, file);
    }
}

//Prints the data from one register
void printData(struct data curData) {
    printf("MARCA DO VEICULO: ");
    if(strlen(curData.brand) > 0) {
        printf("%s\n", curData.brand);
    }
    else {
        printf("NAO PREENCHIDO\n");
    }

    printf("MODELO DO VEICULO: ");
    if(strlen(curData.model) > 0) {
        printf("%s\n", curData.model);
    }
    else {
        printf("NAO PREENCHIDO\n");
    }

    printf("ANO DE FABRICACAO: ");
    if(curData.year != -1) {
        printf("%d\n", curData.year);
    }
    else {
        printf("NAO PREENCHIDO\n");
    }

    printf("NOME DA CIDADE: ");
    if(strlen(curData.city) > 0) {
        printf("%s\n", curData.city);
    }
    else {
        printf("NAO PREENCHIDO\n");
    }

    printf("QUANTIDADE DE VEICULOS: ");
    if(curData.qtt != -1) {
        printf("%d\n", curData.qtt);
    }
    else {
        printf("NAO PREENCHIDO\n");
    }

    printf("\n");
}

//Reads a data from stdin and places in a struct
struct data getParData(int number){
    struct data data = newNullData();
    char buffer;

    for (int i = 0; i < number; ++i) {
        char *search = readstring(stdin, ' ');

        //Tests if the user wants the value to be Null
        char test = getchar();
        char intentional = '0';
        if(test == 'N'){
            scanf("ULO");
            intentional = '1';
        }
        else{
            ungetc(test, stdin);
        }

        if (strcmp(search, "id") == 0) {
            if(intentional == '1'){
                data.id = -2;
            }
            else{
                scanf("%d", &data.id);
            }
        }
        else if (strcmp(search, "ano") == 0) {
            if(intentional == '1'){
                data.year = -2;
            }
            else{
                scanf("%d", &data.year);
            }
        }
        else if (strcmp(search, "qtt") == 0) {
            if(intentional == '1'){
                data.qtt = -2;
            }
            else{
                scanf("%d", &data.qtt);
            }
        }
        else if (strcmp(search, "sigla") == 0) {
            if(intentional == '1'){
                data.initials[0] = '\n';
                data.initials[1] = '\0';
                data.initials[2] = '\0';
            }
            else{
                scanf("\"");

                buffer = fgetc(stdin);
                data.initials[0] = buffer;
                buffer = fgetc(stdin);
                data.initials[1] = buffer;

                data.initials[2] = '\0';
                scanf("\"");
            }
        }
        else if (strcmp(search, "cidade") == 0) {
            if(intentional == '1'){
                data.city = malloc(2);
                data.city[0] = '\n';
                data.city[1] = '\0';
            }
            else{
                scanf("\"");
                data.city = readstring(stdin, '\"');
            }
        }
        else if (strcmp(search, "marca") == 0) {
            if(intentional == '1'){
                data.brand = malloc(2);
                data.brand[0] = '\n';
                data.brand[1] = '\0';
            }
            else{
                scanf("\"");
                data.brand = readstring(stdin, '\"');
            }
        }
        else if (strcmp(search, "modelo") == 0) {
            if(intentional == '1'){
                data.model = malloc(2);
                data.model[0] = '\n';
                data.model[1] = '\0';
            }
            else{
                scanf("\"");
                data.model = readstring(stdin, '\"');
            }
        }
        else {
            printf(ERROR_MSG);
            exit(EXIT_SUCCESS);
        }

        //Skips empty spaces
        buffer = fgetc(stdin);

        free(search);
    }

    if(data.city == NULL) {
        data.city = malloc(1);
        data.city[0] = '\0';
    }

    if(data.brand == NULL) {
        data.brand = malloc(1);
        data.brand[0] = '\0';
    }

    if(data.model == NULL) {
        data.model = malloc(1);
        data.model[0] = '\0';
    }

    //Removes the new line characters
    if (buffer == '\r') {
        buffer = getchar();

        if (buffer != '\n') {
            ungetc(buffer, stdin);
        }
    }

    return data;
}

//Tests if all existing values in one structs are equal to its counterparts in the second struct
char dataComp(struct data parameters, struct data base) {
    if(parameters.id != -1) {
        if(parameters.id == -2 && base.id != -1){
            return '1';
        }
        else if(parameters.id != base.id) {
            return '1';
        }
    }
    if(parameters.year != -1) {
        if(parameters.year == -2 && base.year != -1){
            return '1';
        }
        else if(parameters.year != base.year) {
            return '1';
        }
    }
    if(parameters.qtt != -1) {
        if(parameters.qtt == -2 && base.qtt != -1){
            return '1';
        }
        else if(parameters.qtt != base.qtt) {
            return '1';
        }
    }
    if(parameters.initials[0] != '\0') {
        if(parameters.initials[0] == '\n' && base.initials[0] != '\0'){
            return '1';
        }
        if(strcmp(parameters.initials, base.initials) != 0) {
            return '1';
        }
    }
    if(parameters.city[0] != '\0') {
        if(parameters.city[0] == '\n' && base.city[0] != '\0'){
            return '1';
        }
        if(strcmp(parameters.city, base.city) != 0) {
            return '1';
        }
    }
    if(parameters.brand[0] != '\0') {
        if(parameters.brand[0] == '\n' && base.brand[0] != '\0'){
            return '1';
        }
        if(strcmp(parameters.brand, base.brand) != 0) {
            return '1';
        }
    }
    if(parameters.model[0] != '\0') {
        if(parameters.model[0] == '\n' && base.model[0] != '\0'){
            return '1';
        }
        if(strcmp(parameters.model, base.model) != 0) {
            return '1';
        }
    }

    return '0';
}

//Reads one line of the file and returns a struct with the values
struct data readDataLine(FILE *file) {
    //Creates a struct with null values
    struct data newRegister = newNullData();

    char buffer;

    //Gets the id, if doesn't exist keeps -1
    buffer = fgetc(file);
    if(buffer != 'N') {
        ungetc(buffer, file);
        fscanf(file, "%d", &newRegister.id);
        fgetc(file);
    }
    else{
        fscanf(file, "ULO ");
    }

    //Gets the year, if doesn't exist keeps -1
    buffer = fgetc(file);
    if(buffer != 'N') {
        ungetc(buffer, file);
        fscanf(file, "%d", &newRegister.year);
        fgetc(file);
    }
    else{
        fscanf(file, "ULO ");
    }

    //Gets the quantity, if doesn't exist keeps -1
    buffer = fgetc(file);
    if(buffer != 'N') {
        ungetc(buffer, file);
        fscanf(file, "%d", &newRegister.qtt);
        fgetc(file);
    }
    else{
        fscanf(file, "ULO ");
    }

    //Gets the initials
    buffer = fgetc(file);
    if(buffer != 'N') {
        ungetc(buffer, file);
        fscanf(file, "\"");
        newRegister.initials[0] = fgetc(file);
        newRegister.initials[1] = fgetc(file);
        newRegister.initials[2] = '\0';
        fscanf(file, "\"");
        fgetc(file);
    }
    else{
        fscanf(file, "ULO ");
    }

    //Gets the city
    buffer = fgetc(file);
    if(buffer != 'N') {
        ungetc(buffer, file);
        fscanf(file, "\"");
        newRegister.city = readstring(file, '\"');
        fgetc(file);
    }
    else{
        fscanf(file, "ULO ");
        newRegister.city = malloc(1);
        newRegister.city[0] = '\0';
    }

    //Gets the brand
    buffer = fgetc(file);
    if(buffer != 'N') {
        ungetc(buffer, file);
        fscanf(file, "\"");
        newRegister.brand = readstring(file, '\"');
        fgetc(file);
    }
    else{
        fscanf(file, "ULO ");
        newRegister.brand = malloc(1);
        newRegister.brand[0] = '\0';
    }

    //Gets the model
    buffer = fgetc(file);
    if(buffer != 'N') {
        ungetc(buffer, file);
        fscanf(file, "\"");
        newRegister.model = readstring(file, '\"');
        fgetc(file);
    }
    else{
        fscanf(file, "ULO");
        newRegister.model = malloc(1);
        newRegister.model[0] = '\0';
    }

    //Check if it's the end of file
    buffer = fgetc(file);
    if(buffer == '\r') {
        buffer = fgetc(file);
        if(buffer != '\n') {
            ungetc(buffer, file);
        }
    }
    else if(buffer != '\n') {
        ungetc(buffer, file);
    }

    return newRegister;
}

//Updates the values of a struct to the new values
//Differentiates intentional NULL values from neutral NULL values
struct data changeData(struct data *curData, struct data *changeData){
    struct data newData = *curData;

    if(changeData->id != -1){
        if(changeData->id == -2){
            newData.id = -1;
        }
        else{
            newData.id = changeData->id;
        }
    }
    else{
        newData.id = curData->id;
    }

    if(changeData->year != -1){
        if(changeData->year == -2){
            newData.year = -1;
        }
        else{
            newData.year = changeData->year;
        }
    }
    else{
        newData.year = curData->year;
    }

    if(changeData->qtt != -1){
        if(changeData->qtt == -2){
            newData.qtt = -1;
        }
        else{
            newData.qtt = changeData->qtt;
        }
    }
    else{
        newData.qtt = curData->qtt;
    }

    if(changeData->initials[0] != '\0'){
        if(changeData->initials[0] == '\n'){
            newData.initials[0] = '\0';
        }
        else{
            newData.initials[0] = changeData->initials[0];
            newData.initials[1] = changeData->initials[1];
            newData.initials[2] = changeData->initials[2];
        }
    }
    else{
        newData.initials[0] = curData->initials[0];
        newData.initials[1] = curData->initials[1];
        newData.initials[2] = curData->initials[2];
    }

    if(changeData->city[0] != '\0'){
        if(changeData->city[0] == '\n'){
            newData.city[0] = '\0';
        }
        else{
            newData.city = changeData->city;
        }
    }
    else{
        newData.city = curData->city;
    }

    if(changeData->brand[0] != '\0'){
        if(changeData->brand[0] == '\n'){
            newData.brand[0] = '\0';
        }
        else{
            newData.brand = changeData->brand;
        }
    }
    else{
        newData.brand = curData->brand;
    }

    if(changeData->model[0] != '\0'){
        if(changeData->model[0] == '\n'){
            newData.model[0] = '\0';
        }
        else{
            newData.model = changeData->model;
        }
    }
    else{
        newData.model = curData->model;
    }

    return newData;
}

//Free all the dynamic memory in the data struct
void freeData(struct data *data){
    free(data->city);
    free(data->brand);
    free(data->model);
}