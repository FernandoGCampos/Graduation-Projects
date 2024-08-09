class livro:
    def __init__(self, codigo='', quantidade=0):
        self.codigo = codigo
        self.quantidade = quantidade

    def __str__(self):
        return 'Código: {}\nQuantidade: {}\n'.format(self.codigo, self.quantidade)


class cd:
    def __init__(self, codigo='', quantidade=0):
        self.codigo = codigo
        self.quantidade = quantidade

    def __str__(self):
        return 'Código: {}\nQuantidade: {}\n'.format(self.codigo, self.quantidade)


class dvd:
    def __init__(self, codigo='', quantidade=0):
        self.codigo = codigo
        self.quantidade = quantidade

    def __str__(self):
        return 'Código: {}\nQuantidade: {}\n'.format(self.codigo, self.quantidade)

class Loja:

    def __init__(self):
        self.livros = []
        self.cds = []
        self.dvds = []
        self.numLivros = 0
        self.numCds = 0
        self.numDvds = 0

    def __str__(self):
        string = '===Livros===\n'
        for i in self.livros:
            string += i.__str__()
            string += '\n'

        string += '===CDs===\n'
        for i in self.cds:
            string += i.__str__()
            string += '\n'

        string += '===DVDs===\n'
        for i in self.dvds:
            string += i.__str__()
            string += '\n'

        return string

    def adiciona(self, produto = '', codigo = '', quantidade = 0):
        if produto == 'livro':
            achou = False
            produto = -1
            for i in range(self.numLivros):
                if self.livros[i].codigo == codigo:
                    achou = True
                    produto = i
                    break

            if achou:
                self.livros[produto].quantidade += quantidade
            else:
                self.numLivros += 1
                self.livros.append(livro(codigo = codigo, quantidade = quantidade))

        elif produto == 'cd':
            achou = False
            produto = -1
            for i in range(self.numCds):
                if self.cds[i].codigo == codigo:
                    achou = True
                    produto = i
                    break

            if achou:
                self.cds[produto].quantidade += quantidade
            else:
                self.numCds += 1
                self.cds.append(cd(codigo = codigo, quantidade = quantidade))

        elif produto == 'dvd':
            achou = False
            produto = -1
            for i in range(self.numDvds):
                if self.dvds[i].codigo == codigo:
                    achou = True
                    produto = i
                    break

            if achou:
                self.dvds[produto].quantidade += quantidade
            else:
                self.numDvds += 1
                self.dvds.append(dvd(codigo = codigo, quantidade = quantidade))

        else:
            print('O tipo de produto não é armazenado na loja.\n')

    def remove(self, produto = '', codigo = '', quantidade = 0):
        if produto == 'livro':
            achou = False
            produto = -1
            for i in range(self.numLivros):
                if self.livros[i].codigo == codigo:
                    achou = True
                    produto = i
                    break

            if achou:
                if self.livros[produto].quantidade < quantidade:
                    print('A loja não possui a quantidade desejada. (total = {})\n'.format(self.livros[produto].quantidade))
                elif self.livros[produto].quantidade == quantidade:
                    del self.livros[produto]
                    self.numLivros -= 1
                else:
                    self.livros[produto].quantidade -= quantidade
            else:
                print('Produto não encontrado!\n')

        elif produto == 'cd':
            achou = False
            produto = -1
            for i in range(self.numCds):
                if self.cds[i].codigo == codigo:
                    achou = True
                    produto = i
                    break

            if achou:
                if self.cds[produto].quantidade < quantidade:
                    print('A loja não possui a quantidade desejada. (total = {})\n'.format(self.cds[produto].quantidade))
                elif self.cds[produto].quantidade == quantidade:
                    del self.cds[produto]
                    self.numCds -= 1
                else:
                    self.cds[produto].quantidade -= quantidade
            else:
                print('Produto não encontrado!\n')

        elif produto == 'dvd':
            achou = False
            produto = -1
            for i in range(self.numDvds):
                if self.dvds[i].codigo == codigo:
                    achou = True
                    produto = i
                    break

            if achou:
                if self.dvds[produto].quantidade < quantidade:
                    print('A loja não possui a quantidade desejada. (total = {})\n'.format(self.dvds[produto].quantidade))
                elif self.dvds[produto].quantidade == quantidade:
                    del self.dvds[produto]
                    self.numDvds -= 1
                else:
                    self.dvds[produto].quantidade -= quantidade
            else:
                print('Produto não encontrado!\n')

        else:
            print('O tipo de produto não é armazenado na loja.\n')

    def busca(self, codigo = ''):
        achou = False
        if not achou:
            for i in self.livros:
                if i.codigo == codigo:
                    print(i)
                    achou = True
                    break

        if not achou:
            for i in self.cds:
                if i.codigo == codigo:
                    print(i)
                    achou = True
                    break

        if not achou:
            for i in self.dvds:
                if i.codigo == codigo:
                    print(i)
                    achou = True
                    break

        if not achou:
            print('Produto não encontrado!\n')