#ifndef TRABARQ2_DATA_H
#define TRABARQ2_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_MSG "Falha no processamento do arquivo.\n"
#define HEADER "LISTAGEM DA FROTA DOS VEICULOS NO BRASILCODIGO IDENTIFICADOR: ANO DE FABRICACAO: QUANTIDADE DE VEICULOS: ESTADO: 0NOME DA CIDADE: 1MARCA DO VEICULO: 2MODELO DO VEICULO: "
#define HEADER_SIZE 169

//Save register values
/*
 * Null values are separeted in 2 type:
 * -Intentional = strings "\n" and int -2 (used to change a value to a null value)
 * -Neutral = strings "\0" and int -1 (considered as if it didn't exist)
 */
struct data {
    int id;
    int year;
    int qtt;
    char initials[3]; //Sigla
    char *city;
    char *brand;
    char *model;
};

//Returns a struct with "null" values
struct data newNullData();

//Reads one string in the binary file
char *readBiString(char *code, int *size, FILE *file);

//Writes the data from the struct
void writeBiData(struct data newRegister, FILE* file);

//Prints the data from one register
void printData(struct data curData);

//Reads a data from stdin and places in a struct
struct data getParData(int number);

//Tests if all existing values in one structs are equal to its counterparts in the second struct
char dataComp(struct data data1, struct data data2);

//Reads one line of the file and returns a struct with the values
struct data readDataLine(FILE *file);

//Updates the values of a struct to the new values
//Differentiates intentional NULL values from neutral NULL values
struct data changeData(struct data *curData, struct data *changeData);

//Free all the dynamic memory in the data struct
void freeData(struct data *data);
#endif //TRABARQ2_DATA_H