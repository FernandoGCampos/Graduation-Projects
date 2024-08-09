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

#define NODE2_SIZE 57
#define ID_AMOUNT2 3
#define CHILD_AMOUNT2 4

struct indexNode2{
    char type;
    int ids[ID_AMOUNT2];
    long int offsets[ID_AMOUNT2];
    int idAmount;
    int childs[CHILD_AMOUNT2];
    int childAmount;
};

struct splitNode2{
    int ids[ID_AMOUNT2+1];
    long int offsets[ID_AMOUNT2+1];
    int idAmount;
    int childs[CHILD_AMOUNT2+1];
    int childAmount;
};

//Reads a node from the index file
struct indexNode2 readNode2(FILE* indexFile);

//Writes the node in the index file
void writeNode2(struct indexNode2 node, FILE* indexFile);

//Searches in a node for the position where the id should go
int binSearch2(int id, struct indexNode2 *node);

//Search for the byte offset of a index in the data file
long int searchIndex2(int id, int rrn, FILE* indexFile);

//Search for the byte offset of a index in the data file
long int searchPositionIndex2(int id, FILE* indexFile);

//Splits one node into 2
void split2(int proId, int proDataPos, int proRrn, struct indexNode2 *node,
            int *promoId, long int *promoDataPos, struct  indexNode2 *newNode);

//Inserts one index in the index file
//Returns 1: promotion, 0: not promotion, -1: error
int insertsIndex2(int curRrn, int id, long int dataPos, int *promoId, long int *promoDataPos, int *promoRrn, FILE* indexFile);

//Adds a new index to the file
void addIndex2(int id, long int offset, FILE* indexFile);
#endif //TRABARQ2_INDEX2_H