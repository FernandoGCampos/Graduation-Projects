#include <stdio.h>
#include "comandos.h"

int main(){
    short int comando;
    scanf("%hd ", &comando);

    switch(comando){
        case 1:{
            comando1();
        }
        break;

        case 2:{
            comando2();
        }
        break;

        case 3:{
            comando3();
        }
        break;

        default:{
            printf("O comando %hd não é um comando válido\n\n", comando);
        }
    }
    return 0;
}