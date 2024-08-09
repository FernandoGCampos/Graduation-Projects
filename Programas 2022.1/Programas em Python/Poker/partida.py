class Partida:
    def __init__(self):
        self.creditos = 200

    #Verifica se todas as cartas possuem o mesm naipe
    def mesmo_naipe(self, rodada):
        iguais = True
        naipes = rodada.mao[0].naipe
        for carta in rodada.mao[1: 5]:
            iguais = iguais and naipes == carta.naipe
            if not iguais:
                break

        return iguais

    #Conta o número de cartas que possui cada indice
    def repeticoes(self, rodada):
        valores = []
        for i in range(13):
            valores.append(0)

        for i in rodada.mao:
            valores[i.indice - 1] += 1

        return valores

    #Verifica se todas as cartas estão em sequência
    def sequencia(self, valores):
        #Procura pela carta de menor valor que o jogador tem em mão
        menor = 0
        indice = 0
        while menor == 0 and indice < 9:
            indice += 1
            menor = valores[indice]

        #Verifica se possui uma sequência
        sequencia = True
        contador = 0
        while sequencia and contador < 5 and indice < 13:
            sequencia = sequencia and valores[indice] == 1
            indice += 1
            contador += 1

        return sequencia

    #Descobre qual é a quantidade de vezes que o indice que apareceu mais vezes apareceu
    def maior(self, valores):
        maior = 0
        for i in valores:
            if i > maior:
                maior = i

        return maior

    #Descobre quantos pares apareceram
    def numero_de_pares(self, valores):
        numero_de_pares = 0
        for i in valores:
            if i == 2:
                numero_de_pares += 1

        return numero_de_pares

    #Calcula quanto o jogador ganhou
    def resultado(self, rodada):
        self.creditos -= rodada.aposta
        resultado = rodada.aposta

        #Validações necessárias para saber quanto o jogador deve receber
        mesmo_naipe = self.mesmo_naipe(rodada)
        valores = self.repeticoes(rodada)
        maior = self.maior(valores)
        sequencia = self.sequencia(valores)
        numero_de_pares = self.numero_de_pares(valores)

        #Determina o quanto o jogador deve receber
        if sequencia and mesmo_naipe and valores[0] == 1:
            if valores[0] == 1: #Royal Straight Flush
                resultado *= 200
            else: #Straight Flush
                resultado *= 100
        elif maior == 4: #Quadra
            resultado *= 50
        elif maior == 3 and numero_de_pares == 1: #Full hand
            resultado *= 20
        elif mesmo_naipe: #Flush
            resultado *= 10
        elif sequencia: #Straight
            resultado *= 5
        elif maior == 3: #Trinca
            resultado *= 2
        elif numero_de_pares == 2: #Dois pares
            resultado *= 1
        else: #Resto
            resultado *= 0

        self.creditos += resultado
        return resultado