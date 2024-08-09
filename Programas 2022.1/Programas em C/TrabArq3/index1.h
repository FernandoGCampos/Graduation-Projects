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

#define NODE1_SIZE 45
#define ID_AMOUNT1 3
#define CHILD_AMOUNT1 4

struct indexNode1{
    char type;
    int ids[ID_AMOUNT1];
    int rrns[ID_AMOUNT1];
    int idAmount;
    int childs[CHILD_AMOUNT1];
    int childAmount;
};

struct splitNode1{
    int ids[ID_AMOUNT1+1];
    int rrns[ID_AMOUNT1+1];
    int idAmount;
    int childs[CHILD_AMOUNT1+1];
    int childAmount;
};

//Reads a node from the index file
struct indexNode1 readNode1(FILE* indexFile);

//Writes the node in the index file
void writeNode1(struct indexNode1 node, FILE* indexFile);

//Searches in a node for the position where the id should go
int binSearch1(int id, struct indexNode1 *node);

//Search for the RRN of a index in the data file
int searchIndex1(int id, int rrn, FILE* indexFile);

//Search for the RRN of a index in the data file
int searchRRNIndex1(int id, FILE* indexFile);

//Splits one node into 2
void split1(int proId, int proDataRrn, int proRrn, struct indexNode1 *node,
            int *promoId, int *promoDataRrn, struct  indexNode1 *newNode);

//Inserts one index in the index file
//Returns 1: promotion, 0: not promotion, -1: error
int insertsIndex1(int curRrn, int id, int dataRrn, int *promoId, int *promoDataRrn, int *promoRrn, FILE* indexFile);

//Adds a new index to the file
void addIndex1(int id, int rrn, FILE* indexFile);
#endif //TRABARQ2_INDEX1_H