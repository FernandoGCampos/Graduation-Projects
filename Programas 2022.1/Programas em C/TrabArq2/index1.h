// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all index related functions that only work for files of type 1

#ifndef TRABARQ2_INDEX1_H
#define TRABARQ2_INDEX1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "extralib.h"

struct index1{
    int id;
    int rrn;
};

struct indexArray1{
    int size;
    struct index1 *indexes;
};

//Search for the position of a index in the index array
int searchIndex1(int id, struct indexArray1 *indexArray);

//Adds a new index to the array
void addIndex1(int id, int rrn, struct indexArray1 *indexArray);

//Writes the index array in the index file
void writeIndexes1(struct indexArray1 *indexArray, FILE *file);

//Copies all indexes from a file to an array of structs
struct indexArray1 copyIndexes1(FILE* indexFile);

//Search for the RRN of the corresponding index (returns -1 if doesn't find)
int searchRRNIndex1(int id, struct indexArray1 *indexArray);

//Removes a index from the index array
void removeIndex1(int id, struct indexArray1 *indexArray);

//Swaps the values of the index array
void swapIndex1(int id, int newId, struct indexArray1 *indexArray);

//Updatas the values of the index array
void changeIndex1(int id, int newId, int rrn, struct indexArray1 *indexArray);
#endif //TRABARQ2_INDEX1_H