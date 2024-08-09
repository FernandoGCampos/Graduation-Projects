// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all index related functions that only work for files of type 2

#ifndef TRABARQ2_INDEX2_H
#define TRABARQ2_INDEX2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "extralib.h"

struct index2{
    int id;
    long int offset;
};

struct indexArray2{
    int size;
    struct index2 *indexes;
};

//Search for the position of a index in the index array
int searchIndex2(int id, struct indexArray2 *indexArray);

//Adds a new index to the array
void addIndex2(int id, long int offset, struct indexArray2 *indexArray);

//Writes the index array in the index file
void writeIndexes2(struct indexArray2 *indexArray, FILE *file);

//Copies all indexes from a file to an array of structs
struct indexArray2 copyIndexes2(FILE* indexFile);

//Search for the byte offset of the corresponding index (returns -1 if doesn't find)
long int searchPositionIndex2(int id, struct indexArray2 *indexArray);

//Removes a index from the index array
void removeIndex2(int id, struct indexArray2 *indexArray);

//Swaps the values of the index array
void swapIndex2(int id, int newId, long int offset, struct indexArray2 *indexArray);

//Updatas the values of the index array
void changeIndex2(int id, int newId, long int offset, struct indexArray2 *indexArray);
#endif //TRABARQ2_INDEX2_H