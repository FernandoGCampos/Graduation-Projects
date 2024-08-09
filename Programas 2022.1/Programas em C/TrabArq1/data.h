// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all universal data related functions

#ifndef TRABARQ1_DATA_H
#define TRABARQ1_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_MSG "Falha no processamento do arquivo.\n"
#define HEADER "LISTAGEM DA FROTA DOS VEICULOS NO BRASILCODIGO IDENTIFICADOR: ANO DE FABRICACAO: QUANTIDADE DE VEICULOS: ESTADO: 0NOME DA CIDADE: 1MARCA DO VEICULO: 2MODELO DO VEICULO: "
#define HEADER_SIZE 169

//Save register values
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
char* readBiString(FILE* file, int *size, char* code);

//Reads one line of the csv file and returns a struct with the values
struct data readcsvline(FILE* file, char* buffer);

//Writes the data from the struct
void writeBiData(struct data newRegister, FILE* file);

//Prints the data from one register
void printData(struct data curData);

//Reads a data from stdin and places in a struct
struct data getData(int number);

//Tests if all existing values in one structs are equal to its counterparts in the second struct
char dataComp(struct data data1, struct data data2);

#endif //TRABARQ1_DATA_H
