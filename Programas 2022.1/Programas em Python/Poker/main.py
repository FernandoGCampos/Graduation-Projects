from partida import Partida
from rodada import Rodada

partida = Partida()
print("Saldo atual: ${}.".format(partida.creditos))
while(True):

    rodada = Rodada()
    aposta = rodada.nova_aposta()
    if(aposta == "s"):
        break

    while aposta > partida.creditos or aposta < 0:
        if aposta > partida.creditos:
            print("O valor digitado é maior do que o número de créditos, escolha outro valor.")
        else:
            print("Não se pode apostar um valor negativo, escolha outro valor.")
        aposta = rodada.nova_aposta()

    rodada.embaralha()
    print(rodada)
    for i in range(2):
        trocas = input("Digite os números das cartas que deseja trocar, separados por espaços:")
        rodada.embaralha(trocas)
        print(rodada)


    resultado = partida.resultado(rodada)
    print("Quantidade ganha: ${}.".format(resultado))
    input("Aperte ENTER para continuar...\n")
    if partida.creditos == 0:
        print("A partida acabou porque o jogador perdeu todos os seus créditos.")
        break
    print("Saldo atual: ${}.".format(partida.creditos))