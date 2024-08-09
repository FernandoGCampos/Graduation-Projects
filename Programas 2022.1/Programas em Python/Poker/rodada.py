from cartas import Carta

class Rodada:

    def __init__(self):
        #Guarda cartas que já foram retiradas do baralho
        self.retiradas = []

        #Cartas que o jogador possui em mão
        self.mao = []
        for i in range(5):
            self.mao.append(Carta)
        self.aposta = 0

    #Recebe o input da aposta
    def nova_aposta(self):
        nova_aposta = 0
        while True:
            try:
                entrada = input("Digite o valor da aposta ==> ")
                if entrada == "s":
                    return entrada
                else:
                    nova_aposta = int(entrada)
            except:
                print("Valor digitado inválido, tente novamente.")
                continue
            break

        self.aposta = nova_aposta
        return nova_aposta

    #Retira novas cartas
    def embaralha(self, escolhidas = "1 2 3 4 5"):
        escolhidas = escolhidas.split()
        for i in escolhidas:
            qual = 0
            try:
                qual = int(i)
            except:
                continue
            if qual < 1 or qual > 5:
                continue

            nova_carta = Carta()
            nova_carta.sortear()
            while nova_carta.numeracao in self.retiradas:
                nova_carta.sortear()
            self.retiradas.append(nova_carta.numeracao)
            self.mao[qual - 1] = nova_carta

        resultado = []
        for i in range(5):
            resultado.append(self.mao[i].indice)

        return resultado

    #Imprime as cartas que o jogador tem em mão
    def __str__(self):
        cartas = []
        for i in range(5):
            cartas.append(self.mao[i].imagem())
            cartas[i].append("  ({})   ".format(i + 1))

        impressao = ""
        for i in range(6):
            for j in cartas:
                impressao += j[i]
            impressao += "\n"

        return impressao