// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all functions that only work for files of type 2

#ifndef TRABARQ2_TYPE2_H
#define TRABARQ2_TYPE2_H

#include "extralib.h"
#include "data.h"
#include "index2.h"

void type2(int command);

//Executes the command
void command9_2();
void command10_2();
void command11_2();

//Gets the size of the register
int getDataSize2(struct data reg);

//Reads the data from one register
struct data readBiData2(long int regSize, FILE *file);

//Creates a new register
void addNewReg2(struct data *newRegister, int regSize, FILE* file);

//Ignores one register
void passReg2(FILE* file);

//Places the file pointer at the beginning of non logically removed register
void findReg2(char *buffer, FILE *file);

//Returns the next non logically removed register
struct data getReg2(char *buffer, FILE *file);

//Reuses a logically deleted register
void reuseReg2(struct data *newRegister, int regSize, int maxSize, FILE* file);

//Saves the data in a register
void saveReg2(struct data *newRegister, long int *offset, FILE *file);
#endif //TRABARQ2_TYPE2_H