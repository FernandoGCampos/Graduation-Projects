from contatos import Contato
from contatos import pessoaFisica
from contatos import pessoaJuridica

def search(agenda, nome = '', cpf = '', cnpj = ''):
    achou = False
    i = None
    if nome != '':
        for i in agenda:
            try:
                if nome == i.nome:
                    achou = True
                    break
            except:
                continue

    elif cpf != '':
        for i in agenda:
            try:
                if cpf == i.cpf:
                    achou = True
                    break
            except:
                continue

    elif cnpj != '':
        for i in agenda:
            try:
                if cnpj == i.cnpj:
                    achou = True
                    break
            except:
                continue

    if achou:
        return i
    else:
        return None

def removeContact(agenda, nome = '', cpf = '', cnpj = ''):
    elemento = search(agenda, nome = nome, cpf = cpf, cnpj = cnpj)
    if elemento == None:
        print('Contato nao existe')
    else:
        agenda.remove(elemento)

    return agenda

def newContact():
    tipo = input('Qual o tipo de contato? (fisica/juridica) ')
    if tipo == 'fisica':
        nome = input('Qual o nome? ')
        endereco = input('Qual o endereco? ')
        email = input('Qual o email? ')
        cpf = input('Qual o cpf? ')
        nascimento = input('Qual a data de nascimento? ')
        estadoCivil = input('Qual o estado civil? ')
        print('')

        pessoa = pessoaFisica(_cpf = cpf, _nascimento = nascimento, _estadoCivil = estadoCivil, _nome = nome, _endereco = endereco, _email = email)

    elif tipo == 'juridica':
        nome = input('Qual o nome? ')
        endereco = input('Qual o endereco? ')
        email = input('Qual o email? ')
        cnpj = input('Qual o cnpj? ')
        inscricaoEstadual = input('Qual a inscricao estadual? ')
        razaoSocial = input('Qual a razao social ')
        print('')

        pessoa = pessoaJuridica(_cnpj = cnpj, _inscricaoEstadual = inscricaoEstadual, _razaoSocial = razaoSocial, _nome = nome, _endereco = endereco, _email = email)

    else:
        nome = input('Qual o nome? ')
        endereco = input('Qual o endereco? ')
        email = input('Qual o email? ')
        print('')

        pessoa = Contato(_nome = nome, _endereco = endereco, _email = email)

    return pessoa

def ordena(agenda: Contato):
    pessoaQualquer = []
    pessoaFisica = []
    pessoaJuridica = []
    novaAgenda = []

    for i in range(0, len(agenda)):
        if agenda[i].tipo == 0:
            pessoaQualquer.append(agenda[i])
        elif agenda[i].tipo == 1:
            pessoaFisica.append(agenda[i])
        elif agenda[i].tipo == 2:
            pessoaJuridica.append(agenda[i])

    #Coloca as pessoas nao especificadas na nova agenda
    for i in range(0, len(pessoaQualquer)):
        novaAgenda.append(pessoaQualquer[i])

    #Ordena as pessoas fisicas
    for i in range( 1, len( pessoaFisica ) ):
        chave = pessoaFisica[i]
        k = i
        while k > 0 and chave.cpf < pessoaFisica[k - 1].cpf:
            pessoaFisica[k] = pessoaFisica[k - 1]
            k -= 1
        pessoaFisica[k] = chave

    #Coloca as pessoas fisicas na nova agenda
    for i in range(0, len(pessoaFisica)):
        novaAgenda.append(pessoaFisica[i])

    #Ordena as pessoas juridicas
    for i in range( 1, len( pessoaJuridica ) ):
        chave = pessoaJuridica[i]
        k = i
        while k > 0 and chave.cnpj < pessoaJuridica[k - 1].cnpj:
            pessoaJuridica[k] = pessoaJuridica[k - 1]
            k -= 1
        pessoaJuridica[k] = chave

    #Coloca as pessoas juridicas na nova agenda
    for i in range(0, len(pessoaJuridica)):
        novaAgenda.append(pessoaJuridica[i])

    return novaAgenda

def printAll(agenda):
    for i in range(0, len(agenda)):
        print(i + 1)
        print(agenda[i])