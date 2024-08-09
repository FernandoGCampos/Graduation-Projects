from random import random

#Recebe o valor para "n"
n = int(input("Digite o tamanho da matrix: "))

#Recebe o valor para "p", até receber um input válido
while True:
    p = float(input("Escolha um valor para 'p' (0 < p < 1): "))
    if p <= 0 or p >= 1:    #Checa se a entrada foi válida
        print("Valor de 'p' inválido, tente novamente.")
        continue
    break


#Inicializa a matriz
Grafo = [''] * n

#Loop que passa por linha a linha
i = 0
while i < n:
    Grafo[i] += ' 0 '   #Posiciona o zero redundante (um vértice para ele mesmo)

    #Loop que verifica cada possível aresta que ainda não foi verificada
    j = i + 1
    while j < n:
        x = random()    #Cria um número aleatório entre '0' e '1'

        if x > p:   #Posiciona o '1' indicando que a aresta existe
            Grafo[i] += ' 1 '   #Adiciona ao vértice 'i'
            Grafo[j] += ' 1 '   #Adiciona ao vértice 'j'

        else:   #Posiciona o '0' indicando que a aresta existe
            Grafo[i] += ' 0 '   #Adiciona ao vértice 'i'
            Grafo[j] += ' 0 '   #Adiciona ao vértice 'j'
        j += 1

    i += 1

#Imprime o Grafo
i = 0
while i < n:
    print('|' + Grafo[i] + '|')
    i += 1