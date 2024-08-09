// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that have all index related functions that only work for files of type 2

#include "index2.h"

//Reads a node from the index file
struct indexNode2 readNode2(FILE* indexFile){
    //Creates the node
    struct indexNode2 node;

    //Reads the type
    fread(&node.type, 1, 1, indexFile);

    //Reads the amount of sons
    fread(&node.idAmount, 4, 1, indexFile);
    node.childAmount = node.idAmount + 1;

    //Reads the ids
    for(int i = 0; i < ID_AMOUNT2; ++i){
        fread(&node.ids[i], 4, 1, indexFile);
        fread(&node.offsets[i], 8, 1, indexFile);
    }

    //Reads the sons
    for(int i = 0; i < CHILD_AMOUNT2; ++i){
        fread(&node.childs[i], 4 , 1, indexFile);
    }

    return node;
}

//Writes the node in the index file
void writeNode2(struct indexNode2 node, FILE* indexFile){
    //Writes the type
    fwrite(&node.type, 1, 1, indexFile);

    //Writes the amount of childs
    fwrite(&node.idAmount, 4, 1, indexFile);

    //Writes the ids
    for(int i = 0; i < node.idAmount; ++i){
        fwrite(&node.ids[i], 4, 1, indexFile);
        fwrite(&node.offsets[i], 8, 1, indexFile);
    }
    for(int i = node.idAmount; i < ID_AMOUNT2; ++i){
        int intBuffer = -1;
        long int longBuffer = -1;
        fwrite(&intBuffer, 4, 1, indexFile);
        fwrite(&longBuffer, 8, 1, indexFile);
    }

    //Writes the childs
    for(int i = 0; i < node.childAmount; ++i){
        fwrite(&node.childs[i], 4, 1, indexFile);
    }
    for(int i = node.childAmount; i < CHILD_AMOUNT2; ++i){
        int intBuffer = -1;
        fwrite(&intBuffer, 4, 1, indexFile);
    }
}

//Searches in a node for the position where the id should go
int binSearch2(int id, struct indexNode2 *node){
    int minPos = 0;
    int maxPos = node->idAmount - 1;
    int minId = node->ids[0];
    int maxId = node->ids[maxPos];

    //Checks if already found the position
    if(id > maxId){
        return maxPos + 1;
    }
    else if(id <= minId){
        return 0;
    }
    else if(id == maxId){
        return maxPos;
    }

    //Binary search
    int newPos, newId;
    while(maxPos != minPos){
        //Finds the next "limit" of the binary search
        newPos = (minPos + maxPos) / 2;
        newId = node->ids[newPos];

        //If finds a index that already checked, stops the loop
        if(newId == minId){
            return maxPos;
        }

        //If finds the desired id, returns its position
        else if(newId == id){
            return newPos;
        }

        //Updates the "limits" of the binary search
        else if(newId < id){
            minId = newId;
            minPos = newPos;
        }
        else{
            maxId = newId;
            maxPos = newPos;
        }
    }

    return newPos;
}

//Search for the byte offset of a index in the data file
long int searchIndex2(int id, int rrn, FILE* indexFile){
    //Creates the node buffer
    struct indexNode2 node;

    //Checks if reached the end of the tree
    if(rrn == -1){
        return -1;
    }

    //Reads the node
    else{
        fseek(indexFile, (rrn+1) * NODE2_SIZE, SEEK_SET);
        node = readNode2(indexFile);
    }

    //Finds where the id should be
    int pos = binSearch2(id, &node);

    //If found the id, returns its position
    if(node.ids[pos] == id){
        return node.offsets[pos];
    }

    //Searches in the next node
    else{
        return searchIndex2(id, node.childs[pos], indexFile);
    }
}

//Search for the byte offset of a index in the data file
long int searchPositionIndex2(int id, FILE* indexFile){
    fseek(indexFile, 1, SEEK_SET);
    int root;
    fread(&root, 4, 1, indexFile);

    return searchIndex2(id, root, indexFile);
}

//Splits one node into 2
void split2(int proId, int proDataPos, int proRrn, struct indexNode2 *node,
            int *promoId, long int *promoDataPos, struct  indexNode2 *newNode){
    //Creates a bigger node
    struct splitNode2 splitNode;
    splitNode.idAmount = ID_AMOUNT2+1;
    splitNode.childAmount = CHILD_AMOUNT2+1;

    //Passes all values to the new bigger node
    int pro;
    splitNode.childs[0] = node->childs[0];
    for(pro = 0; pro < ID_AMOUNT2 && node->ids[pro] < proId; ++pro){
        splitNode.ids[pro] = node->ids[pro];
        splitNode.offsets[pro] = node->offsets[pro];
        splitNode.childs[pro+1] = node->childs[pro+1];
    }
    splitNode.ids[pro] = proId;
    splitNode.offsets[pro] = proDataPos;
    splitNode.childs[pro+1] = proRrn;
    for(pro += 1; pro < splitNode.idAmount; ++pro){
        splitNode.ids[pro] = node->ids[pro-1];
        splitNode.offsets[pro] = node->offsets[pro-1];
        splitNode.childs[pro+1] = node->childs[pro];
    }

    //Makes so all values in both nodes are null
    for(int i = 0; i < ID_AMOUNT2; ++i){
        node->ids[i] = -1;
        node->offsets[i] = -1;
        node->childs[i] = -1;
        newNode->ids[i] = -1;
        newNode->offsets[i] = -1;
        newNode->childs[i] = -1;
    }
    node->childs[ID_AMOUNT2] = -1;
    newNode->childs[ID_AMOUNT2] = -1;

    //Changes the amount of indexes in each node
    newNode->idAmount = (splitNode.idAmount - 1)/2;
    newNode->childAmount = newNode->idAmount + 1;
    node->idAmount = splitNode.idAmount - newNode->idAmount - 1;
    node->childAmount = node->idAmount + 1;

    //Places the values of the original node
    node->childs[0] = splitNode.childs[0];
    for(pro = 0; pro < node->idAmount; ++pro){
        node->ids[pro] = splitNode.ids[pro];
        node->offsets[pro] = splitNode.offsets[pro];
        node->childs[pro+1] = splitNode.childs[pro+1];
    }

    //Updates the promotions
    *promoId = splitNode.ids[pro];
    *promoDataPos = splitNode.offsets[pro];

    //Places the values of the new node
    for(int i = 0; i < newNode->idAmount; ++i){
        newNode->ids[i] = splitNode.ids[pro+i+1];
        newNode->offsets[i] = splitNode.offsets[pro+i+1];
        newNode->childs[i] = splitNode.childs[pro+i+1];
    }
    newNode->childs[newNode->idAmount] = splitNode.childs[splitNode.idAmount];

    //Updates the node types
    if(node->childs[0] == -1){
        node->type = '2';
        newNode->type = '2';
    }
    else{
        node->type = '1';
        newNode->type = '1';
    }
}

//Inserts one index in the index file
//Returns 1: promotion, 0: not promotion, -1: error
int insertsIndex2(int curRrn, int id, long int dataPos, int *promoId, long int *promoDataPos, int *promoRrn, FILE* indexFile){
    //Returns promotion
    if(curRrn == -1){
        *promoId = id;
        *promoDataPos = dataPos;
        *promoRrn = -1;
        return 1;
    }
    else{
        //Reads the node
        fseek(indexFile, (curRrn+1) * NODE2_SIZE, SEEK_SET);
        struct indexNode2 node = readNode2(indexFile);

        //Finds where the id should be
        int pos = binSearch2(id, &node);

        //If found the id, returns error message
        if(node.ids[pos] == id){
            printf("ERRO: O índice %d já existe no arquivo de índices!\n", id);
            return -1;
        }

        //Searches in the next nodes
        int proId, proRrn;
        long int proDataPos;
        int returnValue = insertsIndex2(node.childs[pos], id, dataPos, &proId, &proDataPos, &proRrn, indexFile);

        //Returns if found an error, or if doesn't need to promote anymore
        if(returnValue == 0 || returnValue == -1){
            return returnValue;
        }

        //Puts the index in the node if possible
        else if(node.childAmount < CHILD_AMOUNT2){
            //Updates the node struct
            for(int i = ID_AMOUNT2-1; i > pos; --i){
                node.ids[i] = node.ids[i-1];
                node.offsets[i] = node.offsets[i-1];
            }
            for(int i = ID_AMOUNT2; i > pos+1; --i){
                node.childs[i] = node.childs[i-1];
            }
            node.ids[pos] = proId;
            node.offsets[pos] = proDataPos;
            node.childs[pos+1] = proRrn;
            ++node.childAmount;
            ++node.idAmount;

            //Updates the index file
            fseek(indexFile, (curRrn+1) * NODE2_SIZE, SEEK_SET);
            writeNode2(node, indexFile);

            return 0;
        }

        else{
            //Splits the node
            struct indexNode2 newNode;
            split2(proId, proDataPos, proRrn, &node, promoId, promoDataPos, &newNode);

            //Updates the current node
            fseek(indexFile, (curRrn+1) * NODE2_SIZE, SEEK_SET);
            writeNode2(node, indexFile);

            //Creates a node
            fseek(indexFile, 0, SEEK_END);
            writeNode2(newNode, indexFile);

            //Reads the index file header
            int nextNode, nodeAmount;
            fseek(indexFile, 5, SEEK_SET);
            fread(&nextNode, 4, 1, indexFile);
            fread(&nodeAmount, 4, 1, indexFile);

            //Updates the index file header
            fseek(indexFile, 5, SEEK_SET);
            *promoRrn = nextNode;
            ++nextNode;
            ++nodeAmount;

            //Writes the index file header
            fwrite(&nextNode, 4, 1, indexFile);
            fwrite(&nodeAmount, 4, 1, indexFile);

            return 1;
        }
    }
}

//Adds a new index to the file
void addIndex2(int id, long int offset, FILE* indexFile){
    //Reads the root of the tree
    fseek(indexFile, 1, SEEK_SET);
    int root;
    fread(&root, 4, 1, indexFile);

    //Creates the first node of the tree
    if(root == -1){
        //Updates the header
        fseek(indexFile, 1, SEEK_SET);
        int intBuffer = 0;
        fwrite(&intBuffer, 4, 1, indexFile);
        intBuffer = 1;
        fwrite(&intBuffer, 4, 1, indexFile);
        intBuffer = 1;
        fwrite(&intBuffer, 4, 1, indexFile);

        //Creates the first node
        fseek(indexFile, NODE2_SIZE, SEEK_SET);
        fwrite("0", 1, 1, indexFile);

        //Adds the id amount
        intBuffer = 1;
        fwrite(&intBuffer, 4, 1, indexFile);

        //Adds the id
        intBuffer = id;
        fwrite(&intBuffer, 4, 1, indexFile);

        //Adds the position
        long int longBuffer = offset;
        fwrite(&longBuffer, 8, 1, indexFile);

        //Places the null values
        intBuffer = -1;
        longBuffer = -1;
        for(int i = 1; i < ID_AMOUNT2; ++i){
            fwrite(&intBuffer, 4, 1, indexFile);
            fwrite(&longBuffer, 8, 1, indexFile);
        }
        for(int i = 0; i < CHILD_AMOUNT2; ++i){
            intBuffer = -1;
            fwrite(&intBuffer, 4, 1, indexFile);
        }
        return;
    }

    //Inserts the new values in the tree
    int proId, proRrn;
    long int proDataPos;
    int promotion = insertsIndex2(root, id, offset, &proId, &proDataPos, &proRrn, indexFile);

    //If needed it creates a new root
    if(promotion == 1){
        //Reads the header of the index file
        int newRoot, nextNode, nodeAmount;
        fseek(indexFile, 5, SEEK_SET);
        fread(&newRoot, 4, 1, indexFile);
        fread(&nodeAmount, 4, 1, indexFile);

        //Updates the header values
        nextNode = newRoot + 1;
        ++nodeAmount;

        //Changes the header
        fseek(indexFile, 1, SEEK_SET);
        fwrite(&newRoot, 4, 1, indexFile);
        fwrite(&nextNode, 4, 1, indexFile);
        fwrite(&nodeAmount, 4, 1, indexFile);

        //Creates the new root
        fseek(indexFile, (newRoot+1) * NODE2_SIZE, SEEK_SET);

        //Writes the type
        fwrite("0", 1, 1, indexFile);

        //Adds the id amount
        int intBuffer = 1;
        fwrite(&intBuffer, 4, 1, indexFile);

        //Writes the node values
        fwrite(&proId, 4, 1, indexFile);
        fwrite(&proDataPos, 8, 1, indexFile);
        for(int i = 1; i < ID_AMOUNT2; ++i){
            intBuffer = -1;
            long int longBuffer = -1;
            fwrite(&intBuffer, 4, 1, indexFile);
            fwrite(&longBuffer, 8, 1, indexFile);
        }

        //Writes the childs
        fwrite(&root, 4, 1, indexFile);
        fwrite(&proRrn, 4, 1, indexFile);
        for(int i = 2; i < CHILD_AMOUNT2; ++i){
            intBuffer = -1;
            fwrite(&intBuffer, 4, 1, indexFile);
        }
    }
}