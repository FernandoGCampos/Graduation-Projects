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

    #Classe dos componentes do grafo, que salva os vértices e as arestas
    class Componente:
        def __init__(self, valor):
            self.valor = valor
            self.numeroVertices = 0
            self.vertices = []

        #Utilizado para ordenar os componentes
        def __eq__(self, other):
            return self.numeroVertices == other.numeroVertices
        def __ne__(self, other):
            return self.numeroVertices != other.numeroVertices
        def __lt__(self, other):
            return self.numeroVertices < other.numeroVertices
        def __le__(self, other):
            return self.numeroVertices <= other.numeroVertices
        def __gt__(self, other):
            return self.numeroVertices > other.numeroVertices
        def __ge__(self, other):
            return self.numeroVertices >= other.numeroVertices

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

    #Testa para ver se o grafo é conexo
    def testeConexo(self):
        #Caso ele seja direcionado, ele faz uma cópia não direcionada para fazer busca em largura
        if direcionado:
            novoGrafo = self.naoDirecionado()
            novoGrafo.largura(self.vertices[0].indice)
            self.conexo = novoGrafo.conexo

        #Caso ele não seja conexo, apenas faz busca em largura
        else:
            self.largura(self.vertices[0].indice)

        return self.conexo

    #Retorna uma cópia do grafo que não seja direcionado
    def naoDirecionado(self):
        #Cria uma cópia do grafo
        novoGrafo = deepcopy(self)
        novoGrafo.direcionado = False
        novoGrafo.temCiclos = None

        #Verifica qual o tipo de grafo
        if self.direcionado == None:
            return None
        elif not self.direcionado:
            return novoGrafo
        else:
            #Faz com que todas as arestas não sejam direcionadas
            for i in range(self.numeroVertices):
                for j in self.vertices[i].arestas:
                    if i+1 not in self.vertices[j-1].arestas:
                        novoGrafo.vertices[j-1].arestas.append(i+1)

            #Ordena as arestas dos vértices
            for i in range(self.numeroVertices):
                novoGrafo.vertices[i].arestas.sort()

            #Altera os dados sobre a quantidade de conjuntos
            novoGrafo.numeroComponentes = 0
            novoGrafo.componentes = []

            return novoGrafo

    #Realiza a busca em largura a partir de uma raiz e retorna as distâncias
    def largura(self, raiz):
        #Cria as listas das cores dos vértices
        brancos = []
        for i in range(self.numeroVertices):
            brancos.append(i + 1)
        cinzas = []
        pretos = []
        distancias = [-1] * self.numeroVertices

        #Altera a cor da aresta de branco para cinza
        brancos.remove(raiz)
        cinzas.append(raiz)

        #Repete até que não possua mais vértices cinzas
        contador = 0
        while len(cinzas) > 0:

            #Percorre todos os vertices cinzas
            novosCinzas = []
            for vertice in cinzas:
                #Salva a distância do vetor até a raiz
                distancias[vertice - 1] = contador

                #Copia as arestas para uma variavel de mais fácil acesso
                arestas = self.vertices[vertice - 1].arestas
                for aresta in arestas:
                    #Caso encontre algum vértice branco, altera a sua cor para cinza
                    if aresta in brancos:
                        brancos.remove(aresta)
                        novosCinzas.append(aresta)

            #Incrementa o contador
            contador += 1

            #Altera a cor dos vértices de cinza para preto
            for preto in cinzas:
                pretos.append(preto)

            #Atualiza os vértices cinzas
            cinzas = novosCinzas

            #Caso o grafo seja direcionado, ele determina se o grafo é conexo
            if not self.direcionado:
                if len(brancos) > 0:
                    self.conexo = False
                else:
                    self.conexo = True

        #Retorna as distâncias do ponteiro para a raiza
        return distancias

    #Realiza a busca em largura utilizando todos os vértices como raízas
    def larguras(self):
        distancias = []
        for i in range(self.numeroVertices):
            distancias.append(self.largura(i+1))
        return distancias

    #Realiza a busca em profundidade a partir de uma raiz e retorna as distâncias
    def profundidade(self, raiz):
        #Copia os vertices, para poder apagar arestas desnecessárias
        vertices = list(deepcopy(self.vertices[indice]) for indice in range(self.numeroVertices))
        for indice in range(self.numeroVertices):
            vertices[indice].arestas.reverse()

        #Cria as listas das cores dos vértices
        brancos = []
        for i in range(self.numeroVertices):
            brancos.append(i + 1)
        cinzas = []
        pretos = []
        distancias = [-1] * self.numeroVertices

        #Altera a cor da aresta de branco para cinza
        brancos.remove(raiz)
        cinzas.append([raiz,0])

        #Repete até que tenha passado por todos os vértices
        while len(brancos) > 0 or len(cinzas) > 0:
            #Salva os valores do vértice em uma variável de fácil acesso
            cinza = cinzas[len(cinzas) - 1].copy()

            #Escolhe o próximo vértice para ser analisado
            vertice = cinza[0]

            #Salva a distância do vetor até a raiz, caso ele esteja em uma distância "infinita" ele salva -1
            if cinza[1] == -1:
                distancia = -1
                distancias[vertice - 1] = -1
            else:
                distancia = cinza[1] + 1
                distancias[vertice - 1] = distancia - 1
            #Determina se existem novos vértices conectados ao vértice
            final = True

            #Copia as arestas para uma variavel de mais fácil acesso
            arestas = vertices[vertice - 1].arestas

            #Repete o loop até encontrar um vértice branco não ter mais arestas sobrando
            while vertices[vertice - 1].numeroArestas > 0:
                #Le a aresta de menor indice
                vertices[vertice - 1].numeroArestas -= 1
                aresta = arestas.pop()

                #Caso encontre algum vértice branco
                if aresta in brancos:
                    #Altera a sua cor para cinza
                    brancos.remove(aresta)
                    cinzas.append([aresta, distancia])

                    #Marca que ainda não foi encontrado o final
                    final = False

                    #Para a procura nesse vértice
                    break

            #Altera a cor do vértice de cinza para preto
            if final:
                cinzas.pop()
                pretos.append(vertice)

            #Caso ele não possua mais vértices cinzas, ele transforma um vérice branco em cinza
            if len(cinzas) == 0 and len(brancos) > 0:
                #Remove o valor do vetor de vértices brancos
                proxCinza = brancos[0]
                del brancos[0]

                #Adiciona o vértice ao vetor de vértices cinzas
                cinzas.append([proxCinza, -1])

        return distancias

    #Realiza a busca em profundidade utilizando todos os vértices como raízas
    def profundidades(self):
        distancias = []
        for i in range(self.numeroVertices):
            distancias.append(self.profundidade(i + 1))
        return distancias

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

    #Acha os componentes da árvore
    def achaComponentes(self):
        #Segue para o próximo vértice, na busca em profundidade da árvore topológica
        def aprofunda(vertice, ID):
            #Altera o id e o valor
            ids[vertice - 1] = ID
            valor = valores[vertice - 1]= ID
            ID += 1

            #Altera a cor do vértice de branco para cinza
            brancos.remove(vertice)
            cinzas.append(vertice)

            #Busca em todas as arestas do vértice
            for prox in self.vertices[vertice - 1].arestas:
                #Caso encontre algum vértice branco, ele chama a função para esse vértice
                if prox in brancos:
                    aprofunda(prox, ID)

                #Caso ele encontre um vértice cinza, ele altera o valor do vértice para o menor valor entre os dois valores
                elif prox in cinzas:
                    valor = valores[vertice - 1] = min(valores[vertice - 1], valores[prox - 1])


            #Altera a cor dos vértices do conjunto de cinza para preto e cria um conjunto
            if valor == ids[vertice - 1]:
                novoConjunto = self.Componente(vertice)
                while True:
                    #Remove o vértice do vetor de vértices cinzas
                    cinza = cinzas.pop()
                    valores[cinza - 1] = ids[vertice - 1]
                    pretos.append(cinza)

                    #Adiciona um vértice ao conjunto
                    novoConjunto.numeroVertices += 1
                    novoConjunto.vertices.append(cinza)

                    #Interrompe a adição de vértices ao conjunto
                    if cinza == vertice:
                        self.numeroComponentes += 1
                        self.componentes.append(deepcopy(novoConjunto))
                        break

        #Cria os valores do vérices de vértices com:
        #   §indices: Salva quais os vértices em cada posição
        #   §id's: Utilizado para saber quando se completa um conjunto
        #   §valores: Forma de distinguir um grupo de outro
        indices = list(range(1,self.numeroVertices + 1))
        ID = 0
        ids = [0] * self.numeroVertices
        valores = [0] * self.numeroVertices

        #Cria as listas das cores dos vértices
        brancos = []
        for i in range(self.numeroVertices):
            brancos.append(i + 1)
        cinzas = []
        pretos = []

        #Procura em todos os vértices para garantir que encontrou todos os conjuntos
        for indice in indices:
            if indice in brancos:
                aprofunda(indice, ID)

        #Ordena os componentes
        self.componentes.sort()

        #Retorna um vetor com os grupos de cada vértice
        return valores