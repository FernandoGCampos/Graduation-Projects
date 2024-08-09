from copy import deepcopy

#Classe dos grafos, com todos algoritimos utilizados neles
class Grafo:
    #Classe dos vértices do grafo, que salva o índice e as arestas
    class Vertice:
        def __init__(self, indice):
            self.indice = indice
            self.numeroArestas = 0
            self.arestas = []

        def __deepcopy__(self, memodict={}):
            novoVertice = self.__class__(self.indice)
            novoVertice.numeroArestas = self.numeroArestas
            for aresta in self.arestas:
                novoVertice.arestas.append(deepcopy(aresta))
            return novoVertice

    #Inicializa o grafo
    def __init__(self):
        self.numeroVertices = 0
        self.vertices = []
        self.numeroComponentes = 0
        self.componentes = []
        self.conexo = None
        self.direcionado = None
        self.temCiclos = None
        self.arvoreTopologica = None

    #Retorna a string do grafo
    def __str__(self):
        linha = ''
        for i in range(self.numeroVertices):
            for j in range(self.numeroVertices):
                if j + 1 in self.vertices[i].arestas:
                    linha += '1 '
                else:
                    linha += '0 '
            linha += '\n'
        return linha

    #Possibilita fazer cópias inteiramente novas do grafo (permiti alterar vetores da cópia sem alterar a original)
    def __deepcopy__(self, memodict={}):
        novoGrafo = self.__class__()
        novoGrafo.numeroVertices = self.numeroVertices
        novoGrafo.numeroComponentes = self.numeroComponentes
        novoGrafo.direcionado = self.direcionado
        novoGrafo.conexo = self.conexo
        novoGrafo.temCiclos = self.temCiclos
        novoGrafo.arvoreTop = self.arvoreTop
        for vertice in self.vertices:
            novoGrafo.vertices.append(deepcopy(vertice))
        for conjunto in self.componentes:
            novoGrafo.componentes.append(deepcopy(conjunto))
        return novoGrafo

    #Le o grafo a partir do nome de um arquivo
    def leGrafo(self, nomeArquivo):
        try:
            #Abre o arquivo
            arquivo = open(nomeArquivo, 'r')

            #Ignora a palavra "*Vertices "
            arquivo.read(10)

            #Lê o número de vértices
            self.numeroVertices = int(arquivo.readline())

            #Inicializa os vértices
            for i in range(self.numeroVertices):
                self.vertices.append(self.Vertice(i + 1))

            #Verifica se o grafo é direcionado
            direcionado = arquivo.readline()
            if direcionado == '*Arcs\n':
                self.direcionado = True
            elif direcionado == '*Edges\n':
                self.direcionado = False

            #Lê as arestas
            arestas = arquivo.readlines()

            for aresta in arestas:
                try:
                    #Lê os índices dos vértices
                    aresta = aresta.replace("\n", "")
                    aresta = aresta.split(sep=' ')
                    aresta[0] = int(aresta[0])
                    aresta[1] = int(aresta[1])

                    #Incrementa o número de arestas dos vértices
                    self.vertices[aresta[0] - 1].numeroArestas += 1

                    #Adiciona as arestas aos vértices
                    self.vertices[aresta[0] - 1].arestas.append(aresta[1])

                    #Verifica se o grafo é não direcionado
                    if not self.direcionado:
                        self.vertices[aresta[1] - 1].numeroArestas += 1
                        self.vertices[aresta[1] - 1].arestas.append(aresta[0])

                except:
                    #Evita que erros ocorram
                    nada = None

            #Ordena as arestas dos vértices
            for i in range(self.numeroVertices):
                self.vertices[i].arestas.sort()

        except:
            #Informa caso não consiga ler o arquivo
            print("Falha ao ler o arquivo")

        finally:
            #Fecha o arquivo
            arquivo.close()

    #Acha a árvore topológicam, e determina se o grafo é cíclico
    def ordenacaoTopologica(self):
        # Segue para o próximo vértice, na busca em profundidade da árvore topológica
        def aprofunda(vertice):
            # Altera a cor do vértice de branco para cinza
            brancos.remove(vertice)
            cinzas.append(vertice)

            # Busca em todas as arestas do vértice
            for prox in self.vertices[vertice - 1].arestas:
                # Caso encontre outro vértice cinza, ele informa que o grafo é cíclico
                if prox in cinzas:
                    self.temCiclos = True

                # Caso encontre algum vértice branco, ele repete o algoritmo
                elif prox in brancos:
                    aprofunda(prox)

            # Altera a cor do vértice de cinza para preto
            cinzas.remove(vertice)
            pretos.append(vertice)

        # Cria as listas das cores dos vértices
        brancos = []
        for i in range(self.numeroVertices):
            brancos.append(i + 1)
        cinzas = []
        pretos = []

        #Executa o código até que não tenham mais vértices brancos
        while len(brancos) > 0:
            raiz = brancos[0]
            aprofunda(raiz)

        #Retorna a árvore topológica
        self.arvoreTopologica = pretos.copy()
        self.arvoreTopologica.reverse()
        return self.arvoreTopologica

if __name__ == "__main__":
    #Cria o grafo
    nomeArquivo = input()
    grafo = Grafo()
    grafo.leGrafo(nomeArquivo)

    #Realiza a busca em profundidade e descobre se ele é cíclico
    grafo.ordenacaoTopologica()

    # Imprime o resultado
    if grafo.direcionado != None:
        if grafo.temCiclos:
            print('S')
        else:
            print('N')