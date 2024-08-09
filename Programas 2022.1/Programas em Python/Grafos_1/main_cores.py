import random
from random import random

#Recebe os valores para "n" e para "p"
n = int(input('Digite o tamanho da matrix: '))
p = float(input('Escolha um valor para "p" (0 < p < 1): '))

#Inicializa a matriz
Grafo = [''] * n

i = 0
while i < n:
    j = i + 1
    Grafo[i] += '\033[1;34m 0 '
    while j < n:
        x = random()
        if x > p:
            Grafo[i] += '\033[1;32m 1 '
            Grafo[j] += '\033[1;32m 1 '
        else:
            Grafo[i] += '\033[1;31m 0 '
            Grafo[j] += '\033[1;31m 0 '
        j += 1
    i += 1

#Imprime o Grafo
i = 0
while i < n:
    print('\033[;7m|' + Grafo[i] + '\033[;7m|\033[0;0m')
    i += 1