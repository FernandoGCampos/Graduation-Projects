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
char* readBiString(FILE* file, int *size, char* code) {
    char* string;
    int buffer;
    fread(&buffer, 4, 1, file);

    *size = buffer;
    fread(code, 1, 1, file);

    string = malloc(buffer + 1);
    fread(string, 1, buffer, file);
    string[buffer] = '\0';

    return string;
}

//Reads one line of the csv file and returns a struct with the values
struct data readcsvline(FILE* file, char* buffer) {
    //Creates a struct with null values
    struct data newRegister = newNullData();

    //Checks if it's the end of the file inputs
    *buffer = fgetc(file);
    if(*buffer == EOF) {
        return newRegister;
    }

    //Gets the id, if doesn't exist keeps -1
    if(*buffer != ',') {
        ungetc(*buffer, file);
        fscanf(file, "%d,", &newRegister.id);
    }

    //Gets the year, if doesn't exist keeps -1
    *buffer = fgetc(file);
    if(*buffer != ',') {
        ungetc(*buffer, file);
        fscanf(file, "%d,", &newRegister.year);
    }

    //Gets the city
    newRegister.city = readstring(file, ',');

    //Gets the quantity, if doesn't exist keeps -1
    *buffer = fgetc(file);
    if(*buffer != ',') {
        ungetc(*buffer, file);
        fscanf(file, "%d,", &newRegister.qtt);
    }

    //Gets the initials
    *buffer = fgetc(file);
    if(*buffer != ',') {
        ungetc(*buffer, file);
        newRegister.initials[0] = fgetc(file);
        newRegister.initials[1] = fgetc(file);
        newRegister.initials[2] = '\0';
        fgetc(file);
    }

    //Gets the brand
    newRegister.brand = readstring(file, ',');

    //Gets the model
    newRegister.model = readstring(file, ',');

    //Check if it's the end of file
    *buffer = fgetc(file);
    if(*buffer == '\r') {
        *buffer = fgetc(file);
        if(*buffer != '\n') {
            ungetc(*buffer, file);
        }
    }
    else if(*buffer != '\n') {
        ungetc(*buffer, file);
    }

    return newRegister;
}

//Writes the data from the struct
void writeBiData(struct data newRegister, FILE* file) {
    //Writes the fix size data
    fwrite(&newRegister.id, 4, 1, file);
    fwrite(&newRegister.year, 4, 1, file);
    fwrite(&newRegister.qtt, 4, 1, file);
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
struct data getData(int number){
    struct data searchData = newNullData();
    for (int i = 0; i < number; ++i) {
        char *search = readstring(stdin, ' ');
        if (strcmp(search, "id") == 0) {
            scanf("%d", &searchData.id);
        }
        else if (strcmp(search, "ano") == 0) {
            scanf("%d", &searchData.year);
        }
        else if (strcmp(search, "qtt") == 0) {
            scanf("%d", &searchData.qtt);
        }
        else if (strcmp(search, "sigla") == 0) {
            scanf("\"%s\"", searchData.initials);
        }
        else if (strcmp(search, "cidade") == 0) {
            scanf("\"");
            searchData.city = readstring(stdin, '\"');
        }
        else if (strcmp(search, "marca") == 0) {
            scanf("\"");
            searchData.brand = readstring(stdin, '\"');
        }
        else if (strcmp(search, "modelo") == 0) {
            scanf("\"");
            searchData.model = readstring(stdin, '\"');
        }
        else {
            printf(ERROR_MSG);
            exit(EXIT_SUCCESS);
        }

        free(search);
        //Removes the new line characters
        char newLineRemove = getchar();
        if (newLineRemove == '\r') {
            newLineRemove = getchar();

            if (newLineRemove != '\n') {
                ungetc(newLineRemove, stdin);
            }
        }
    }

    if(searchData.city == NULL) {
        searchData.city = malloc(1);
        searchData.city[0] = '\0';
    }

    if(searchData.brand == NULL) {
        searchData.brand = malloc(1);
        searchData.brand[0] = '\0';
    }

    if(searchData.model == NULL) {
        searchData.model = malloc(1);
        searchData.model[0] = '\0';
    }

    return searchData;
}

//Tests if all existing values in one structs are equal to its counterparts in the second struct
char dataComp(struct data parameters, struct data base) {

    if(parameters.id != -1) {
        if(base.id == -1 || parameters.id != base.id) {
            return '1';
        }
    }
    if(parameters.year != -1) {
        if(base.year == -1 || parameters.year != base.year) {
            return '1';
        }
    }
    if(parameters.qtt != -1) {
        if(base.qtt == -1 || parameters.qtt != base.qtt) {
            return '1';
        }
    }
    if(parameters.initials[0] != '\0') {
        if(base.initials[0] == '\0' || strcmp(parameters.initials, base.initials) != 0) {
            return '1';
        }
    }
    if(strlen(parameters.city) > 0) {
        if(strlen(base.city) == 0 || strcmp(parameters.city, base.city) != 0) {
            return '1';
        }
    }
    if(strlen(parameters.brand) > 0) {
        if(strlen(base.brand) == 0 || strcmp(parameters.brand, base.brand) != 0) {
            return '1';
        }
    }
    if(strlen(parameters.model) > 0) {
        if(strlen(base.model) == 0 || strcmp(parameters.model, base.model) != 0) {
            return '1';
        }
    }

    return '0';
}