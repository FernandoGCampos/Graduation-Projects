// Turma: A     Equipe: G32
// Alunos: Bernardo Rodrigues Tameirão Santos   Nº USP: 12733212
//         Fernando Gonçalves Campos                    12542352

//File that can't be placed in any other file

#ifndef TRABARQ1_EXTRALIB_H
#define TRABARQ1_EXTRALIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_MSG "Falha no processamento do arquivo.\n"
#define HEADER "LISTAGEM DA FROTA DOS VEICULOS NO BRASILCODIGO IDENTIFICADOR: ANO DE FABRICACAO: QUANTIDADE DE VEICULOS: ESTADO: 0NOME DA CIDADE: 1MARCA DO VEICULO: 2MODELO DO VEICULO: "
#define HEADER_SIZE 169

//Reads a string in a file until finds a parameter o new line indicator
char* readstring(FILE* file, char parameter);

//Tries to open a file and exits the program if its unable to
FILE *openFile(char *fileName, char *method);

//Test file status
void testStatus(FILE* file);

void binarioNaTela(char *nomeArquivoBinario);
#endif //TRABARQ1_EXTRALIB_H