#ifndef EXERCICIO_1_ARQUIVOS_FUNCOES_H
#define EXERCICIO_1_ARQUIVOS_FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
void binarioNaTela(char *nomeArquivoBinario);
void adiciona_pessoa(FILE* arquivo);
void imprime_registro(FILE* arquivo);

#endif //EXERCICIO_1_ARQUIVOS_FUNCOES_H
