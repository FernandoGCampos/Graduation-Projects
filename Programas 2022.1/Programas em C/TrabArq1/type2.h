// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all functions that only work for files of type 2

#ifndef TRABARQ1_TYPE2_H
#define TRABARQ1_TYPE2_H

#include "extralib.h"
#include "data.h"

//Chooses what command to execute
void type2(char command);

//Executes the command
void command1_2();
void command2_2();
void command3_2();

//Gets the size of the register
int getDataSize2(struct data reg);

//Reads the data from one register
struct data readBiData2(FILE* file, long int regSize);

//Creates a new register
void addNewReg2(struct data *newRegister, int regSize, FILE* file);

//Ignores one register
void passReg2(FILE* file);

//Places the file pointer at the beginning of non logically removed register
void findReg2(FILE* file, char* buffer);

//Returns the next non logically removed register
struct data getReg2(FILE* file, char* buffer);

#endif //TRABARQ1_TYPE2_H
