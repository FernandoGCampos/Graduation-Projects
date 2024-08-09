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

void type1(int command);

//Executes the command
void command9_1();
void command10_1();
void command11_1();

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

//Reuses a logically deleted register
void reuseReg1(struct data *newRegister, int dataSize, FILE* file);

//Saves the data in a register
void saveReg1(struct data *newRegister, int *rrn, FILE *file);
#endif //TRABARQ2_TYPE1_H