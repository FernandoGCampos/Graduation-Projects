// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all index related functions that only work for files of type 2

#include "index2.h"

//Search for the position of a index in the index array
int searchIndex2(int id, struct indexArray2 *indexArray){
        //Initializes the values of the positions of the limits in the index array
        int maxPosition = indexArray->size-1;
        int minPosition = 0;

        //Initializes the values of the ids of the limits in the index array
        int idMax = indexArray->indexes[maxPosition].id;
        int idMin = indexArray->indexes[0].id;

        //Repeates the binary search until find the id
        while(maxPosition != minPosition){
            //If the desired id isn't in range, the loop stops
            if(idMin > id || idMax < id){
                break;
            }
            else{
                //Finds the next "limit" of the binary search
                int newPosition = (minPosition + maxPosition) / 2;
                int newId = indexArray->indexes[newPosition].id;

                //If finds a index that already checked, stops the loop
                if(newId == idMin || newId == idMax){
                    break;
                }

                //If the id is the desired one, then the program returns the position in the data file
                if(newId == id){
                    return newPosition;
                }

                //Updates the "limits" of the binary search
                else if(newId < id){
                    idMin = newId;
                    minPosition = newPosition;
                }
                else{
                    idMax = newId;
                    maxPosition = newPosition;
                }
            }
        }
        return -1;
}

//Adds a new index to the array
void addIndex2(int id, long int offset, struct indexArray2 *indexArray){
    //Increases the size of the index array
    ++indexArray->size;
    int size = indexArray->size;
    indexArray->indexes = realloc(indexArray->indexes, size * sizeof(struct index2));

    //Initializes the values of the new index
    indexArray->indexes[size - 1].id = id;
    indexArray->indexes[size - 1].offset = offset;

    //Places the new index in the correct position
    for(int i = size - 1; i > 0; --i){
        if(indexArray->indexes[i-1].id > id){
            struct index2 buffer = indexArray->indexes[i - 1];
            indexArray->indexes[i-1] = indexArray->indexes[i];
            indexArray->indexes[i] = buffer;
        }
    }
}

//Writes the index array in the index file
void writeIndexes2(struct indexArray2 *indexArray, FILE *file){
    int size = indexArray->size;

    for(int i = 0; i < size; ++i){
        fwrite(&indexArray->indexes[i].id, 4, 1, file);
        fwrite(&indexArray->indexes[i].offset, 8, 1, file);
    }
}

//Copies all indexes from a file to an array of structs
struct indexArray2 copyIndexes2(FILE* indexFile){
    struct indexArray2 indexArray;
    indexArray.size = 0;
    indexArray.indexes = malloc(0);

    char buffer = ' ';
    while(fread(&buffer, 1, 1, indexFile) != 0){
        fseek(indexFile, -1, SEEK_CUR);

        ++indexArray.size;
        int size = indexArray.size;
        indexArray.indexes = realloc(indexArray.indexes, size * sizeof(struct index2));
        fread(&indexArray.indexes[size-1].id, 4, 1, indexFile);
        fread(&indexArray.indexes[size-1].offset, 8, 1, indexFile);
    }

    return indexArray;
}

//Search for the byte offset of the corresponding index (returns -1 if doesn't find)
long int searchPositionIndex2(int id, struct indexArray2 *indexArray){
    //Search for the index in the array
    int position = searchIndex2(id, indexArray);

    //Returns the value that was found
    if(position == -1){
        return -1;
    }
    else{
        return indexArray->indexes[position].offset;
    }
}

//Removes a index from the index array
void removeIndex2(int id, struct indexArray2 *indexArray){
    int position = searchIndex2(id, indexArray);

    if(position != -1){
        //Moves all values after the value to be removed, one space backwards
        for(int i = position + 1; i < indexArray->size; ++i){
            indexArray->indexes[i - 1] = indexArray->indexes[i];
        }

        //Reduces the size of the array
        --indexArray->size;
        indexArray->indexes = realloc(indexArray->indexes, indexArray->size * sizeof(struct index2));
    }
}

//Swaps the values of the index array
void swapIndex2(int id, int newId, long int offset, struct indexArray2 *indexArray){
    int position = searchIndex2(id, indexArray);

    if(position != -1){
        indexArray->indexes[position].id = newId;
        indexArray->indexes[position].offset = offset;

        //Sorts the new value for the index in the array
        struct index2 buffer = indexArray->indexes[position];

        //If the value is in a higher position than it needed to be, moves it to the correct position
        if(position > 0 && indexArray->indexes[position - 1].id > newId){
            int i;
            for(i = position; i > 0 && indexArray->indexes[i - 1].id > newId; --i){
                indexArray->indexes[i] = indexArray->indexes[i - 1];
            }
            indexArray->indexes[i] = buffer;
        }

        //If the value is in a lower position than it needed to be, moves it to the correct position
        else if(position < indexArray->size - 1 && indexArray->indexes[position + 1].id < newId){
            int i;
            for(i = position + 1; i < indexArray->size && indexArray->indexes[i + 1].id < newId; ++i){
                indexArray->indexes[i - 1] = indexArray->indexes[i];
            }
            indexArray->indexes[i] = buffer;
        }
    }
}

//Updatas the values of the index array
void changeIndex2(int id, int newId, long int offset, struct indexArray2 *indexArray){
    //Tests if the "file" (array of indexes) already has a index
    if(id != -1){
        if(newId == -1){
            removeIndex2(id, indexArray);
        }
        else{
            swapIndex2(id, newId, offset, indexArray);
        }
    }

    //If needed it adds a new index to the file
    else if(newId != -1){
        addIndex2(newId, offset, indexArray);
    }
}