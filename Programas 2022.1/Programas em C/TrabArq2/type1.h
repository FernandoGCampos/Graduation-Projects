// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all functions that only work for files of type 1

#ifndef TRABARQ2_TYPE1_H
#define TRABARQ2_TYPE1_H

#include "extralib.h"
#include "data.h"
#include "index1.h"

#define REG_SIZE 97

//Save multiple positions of registers
struct positionsArray1{
    int size;
    int* rrns;
    int idAmount;
    int* ids;
};

void type1(char command);

//Executes the command
void command5_1();
void command6_1();
void command7_1();
void command8_1();

//Gets the size of the register
int getDataSize1(struct data reg);

//Reads the data from one register
struct data readBiData1(FILE *file);

//Creates a new register
void addNewReg1(struct data *newRegister, FILE* file);

//Places the file pointer at the beginning of non logically removed register
void findReg1(char *buffer, FILE *file);

//Returns the next non logically removed register
struct data getReg1(char *buffer, FILE *file);

//Searchs for the RRN of the corresponding data
struct positionsArray1 searchData1(struct data *searchData, FILE* binFile);

//Reuses a logically deleted register
void reuseReg1(struct data *newRegister, int dataSize, FILE* file);

//Saves the data in a register
void saveReg1(struct data *newRegister, int *rrn, FILE *file);

//Removes one register
void removeReg1(int rrn, FILE *binFile);
#endif //TRABARQ2_TYPE1_H