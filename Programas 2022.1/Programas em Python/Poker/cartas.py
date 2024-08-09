from random import random

class Carta:
    def __init__(self):
        #Valor da carta
        self.indice = 0

        #Naipe da carta
        self.naipe = 0

        #Inteiro único para cada par índice/naipe utilizado para distinguir as cartas
        self.numeracao = 0

    #Altera o indice e o naipe da carta aleatoriamente
    def sortear(self):
        self.indice = int((random() * 13) + 1)
        self.naipe = int(random() * 4)
        self.numeracao = (self.naipe * 13) + self.indice
        return (self.indice , self.naipe)

    #Retorna a imagem da carta separada em linhas
    def imagem(self):
        # Posiciona o topo da carta
        linhas = []
        linhas.append("+-----+ ")
        linhas.append("|     | ")
        linhas.append("| ")

        # Posiciona o índice
        if self.indice == 1:
            linhas[2] += "A "
        elif self.indice == 11:
            linhas[2] += "J "
        elif self.indice == 12:
            linhas[2] += "Q "
        elif self.indice == 13:
            linhas[2] += "K "
        elif self.indice >= 1 and self.indice <= 13:
            linhas[2] += "{0:<2}".format(self.indice)
        else:
            linhas[2] += "E "

        # Posiciona o naipe
        if self.naipe == 0:
            linhas[2] += "{:<2}| ".format("♠")
        elif self.naipe == 1:
            linhas[2] += "{:<2}| ".format("♣")
        elif self.naipe == 2:
            linhas[2] += "{:<2}| ".format("♥")
        elif self.naipe == 3:
            linhas[2] += "{:<2}| ".format("♦")
        else:
            linhas[2] += "E | "

        # Posiciona o inferior da carta
        linhas.append("|     | ")
        linhas.append("+-----+ ")

        return linhas

    def __str__(self):
        impressao = ""
        linhas = self.imagem()

        for i in linhas:
            impressao += i + "\n"

        return impressao