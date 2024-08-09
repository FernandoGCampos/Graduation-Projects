// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//Possible optimization:
/*  Instead of working directly on the header of both files we could create variables to save the header values
 *and only update it in the end of the execution*/

#include <stdio.h>
#include "type1.h"
#include "type2.h"

#define ERROR_MSG "Falha no processamento do arquivo.\n"

int main() {
    int command;
    char type;

    scanf("%d ", &command);
    scanf("tipo%c ", &type);

    switch(type) {
        case '1':
            type1(command);
            break;

        case '2':
            type2(command);
            break;

        default:
            printf(ERROR_MSG);
    }
    return 0;
}