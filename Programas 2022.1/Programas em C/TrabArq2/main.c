// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//Falta fazer os comandos do tipo 1

#include <stdio.h>
#include "type1.h"
#include "type2.h"

#define ERROR_MSG "Falha no processamento do arquivo.\n"

int main() {
    char command;
    char type;

    scanf("%c ", &command);
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