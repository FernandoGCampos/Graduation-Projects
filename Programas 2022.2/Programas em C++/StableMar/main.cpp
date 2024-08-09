#include <iostream>

int main() {
    //Lê o número de testes
    int testes;
    scanf("%d ", &testes);
    for(int n = 0; n < testes; ++n){
        int bufferInt;

        //Lê o número de casamentos
        int casamentos = 0;
        scanf("%d ", &casamentos);

        //Lê as preferências das mulheres
        int **mulheres = (int**) malloc(casamentos * sizeof(int*));
        for(int i = 0; i < casamentos; ++i){
            //Lê o indice, que pode ser ignorado nesse caso
            scanf("%d ", &bufferInt);

            mulheres[i] = (int*) malloc(casamentos * sizeof(int));
            for(int j = 0; j < casamentos; ++j){
                scanf("%d ", &mulheres[i][j]);
                --mulheres[i][j];
            }
        }

        //Lê as preferências dos homens
        int **homens = (int**) malloc(casamentos * sizeof(int*));
        for(int i = 0; i < casamentos; ++i){
            //Lê o indice, que pode ser ignorado nesse caso
            scanf("%d ", &bufferInt);

            homens[i] = (int*) malloc(casamentos * sizeof(int));
            for(int j = 0; j < casamentos; ++j){
                scanf("%d ", &homens[i][j]);
                --homens[i][j];
            }
        }

        //Salva os relacionamentos das pessoas
        int relacoesM[casamentos];
        int relacoesH[casamentos];
        bool casadas[casamentos];
        for(int i = 0; i < casamentos; ++i){
            relacoesM[i] = -1;
            relacoesH[i] = -1;
            casadas[i] = false;
        }

        //Efetua os casamentos
        int preferencia = 0;
        int solteiros = casamentos;
        while(solteiros > 0 && preferencia < casamentos){
            for(int i = 0; i < casamentos; ++i){
                //Verifica se o homem já esta casado
                if(relacoesH[i] == -1){
                    //Salva o valor da mulher de interesse do homem
                    int proposta = homens[i][preferencia];

                    //Salva o valor do homem que já esta em relação com a mulher
                    int disputa = relacoesM[proposta];

                    //Caso a mulher não esteja em relacionamento, ela aceita a proposta
                    if(disputa == -1){
                        relacoesM[proposta] = i;
                        relacoesH[i] = proposta;
                    }

                    //Caso a mulher esteja em relacionamento, ela compara os dois homens
                    else{
                        //Descobre qual dos dois é de maior interesse
                        int escolha;
                        for(int j = 0; j < casamentos; ++j){
                            escolha = mulheres[proposta][j];
                            if(escolha == i || escolha == disputa){
                                break;
                            }
                        }

                        //Altera os dados dos relacionamentos das pessoas envolvidas
                        if(escolha == i){
                            relacoesM[proposta] = i;
                            relacoesH[i] = proposta;
                            relacoesH[disputa] = -1;
                        }
                    }
                }
            }

            //Efetua o casamento, impossibilitando, os membros a se relacionarem com outras pessoas
            for(int i = 0; i < casamentos; ++i){
                if(!casadas[i]){
                    if(relacoesM[i] != -1){
                        casadas[i] = true;
                        --solteiros;
                    }
                }
            }

            ++preferencia;
        }

        //Imprime os casamentos
        for(int i = 0; i < casamentos; ++i){
            printf("%d %d\n", i+1, relacoesH[i]+1);
        }

        //Libera a memória
        for(int i = 0; i < casamentos; ++i){
            free(mulheres[i]);
            free(homens[i]);
        }
        free(mulheres);
        free(homens);
    }
    return 0;
}
