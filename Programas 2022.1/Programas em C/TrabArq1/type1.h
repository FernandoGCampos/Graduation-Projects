// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all functions that only work for files of type 1

#ifndef TRABARQ1_TYPE1_H
#define TRABARQ1_TYPE1_H

#include "extralib.h"
#include "data.h"

#define REG_SIZE 97

//Chooses what command to execute
void type1(char command);

//Executes the command
void command1_1();
void command2_1();
void command3_1();
void command4_1();

//Gets the size of the register
int getDataSize1(struct data reg);

//Reads the data from one register
struct data readBiData1(FILE* file);

//Creates a new register
void addNewReg1(struct data *newRegister, FILE* file);

//Places the file pointer at the beginning of non logically removed register
void findReg1(FILE* file, char* buffer);

//Returns the next non logically removed register
struct data getReg1(FILE* file, char* buffer);

#endif //TRABARQ1_TYPE1_H
