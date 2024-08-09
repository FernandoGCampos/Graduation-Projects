from Turmas import Turma
from Grupos import Grupo
from Alunos import Aluno

class Trabalho:
    def __init__(self, numTurmas):
        #Adiciona todas as turmas
        # Ele irá numerar as turmas na ordem em que os arquivos foram abertos com sucesso
        # Não necessariamente o número da turma na realidade será igual ao que o programa irá considerar
        self.turmas = []
        for i in range(numTurmas):
            nomeArquivo = input('Digite o nome do arquivo da turma: ')
            turma = Turma(nomeArquivo)
            if turma.existe:
                self.turmas.append(turma)
            else:
                print('FALHA AO PROCESSAR O ARQUIVO DA TURMA!\n')
        print('')

        #Salva o número de turmas cujos arquivos foram abertos com sucesso
        self.numTurmas = len(self.turmas)

        #Salva os grupos
        self.grupos = []

        #Guardam grupos inválidos, que precisam ser arrumados
        self.maiores = []
        self.menores = []
        self.mistos = []
        self.inexistentes = []

    #Cria uma string com todos os dados importantes dos grupos formados
    def __str__(self):
        string = ''
        for i in range(self.numTurmas):
            if len(self.turmas[i].grupos) > 0 or len(self.turmas[i].semGrupo) > 0:
                string += '=========================Turma {}=========================\n'.format(i+1)

            if len(self.turmas[i].grupos) > 0:
                string += '--------------------Grupos--------------------\n'
                for j in self.turmas[i].grupos:
                    string += j.__str__()
                    string += '\n'

            if len(self.turmas[i].semGrupo) > 0:
                string += '---------------Alunos sem grupo---------------\n'
                for j in self.turmas[i].semGrupo:
                    string += j.__str__()
                string += '\n'

            if len(self.turmas[i].alunosRepetem) > 0:
                string += '-----Alunos que estão em mais de um grupo-----\n'
                for j in self.turmas[i].alunosRepetem:
                    string += j.__str__()
                string += '\n'

        if len(self.maiores) > 0:
            string += '======================Grupos Maiores======================\n'
            for j in self.maiores:
                string += j.__str__()
                string += '\n'

        if len(self.menores) > 0:
            string += '======================Grupos Menores======================\n'
            for j in self.menores:
                string += j.__str__()
                string += '\n'

        if len(self.mistos) > 0:
            string += '================Grupos de multiplas turmas================\n'
            for j in self.mistos:
                string += j.__str__()
                string += '\n'

        if len(self.inexistentes) > 0:
            string += '==============Grupos com alunos inexistentes==============\n'
            for j in self.inexistentes:
                string += j.__str__()
                string += '\n'

        return string

    def novoGrupo(self, nomeArquivo):
        grupo = Grupo(nomeArquivo)
        if grupo.existe:
            #Verifica se o grupo tem mais membros do que se é permitido
            if grupo.tamanho > 4:
                print('O grupo possuí mais membros do que se é permitido!')
                self.maiores.append(grupo)

            # Verifica se o grupo tem menos membros do que se é permitido
            if grupo.tamanho < 4:
                print('O grupo possuí menos membros do que se é permitido!')
                self.menores.append(grupo)

            #Verifica se o grupo é um grupo válido
            existem = True
            misto = False
            turma = 0

            #Verifica todos os membros do grupo
            for i in grupo.membros:
                existe = False

                #Verifica em todas as turmas
                contador = 0
                for j in self.turmas:
                    contador += 1
                    if i in j.alunos:
                        existe = True

                        #Verifica se o membro é da mesma turma que alunos do grupo
                        if turma != 0 and turma != contador:
                            misto = True
                        else:
                            turma = contador

                        #Retira o aluno do grupo de alunos que não possuem grupo ou informa que ele esta repetindo
                        if i in j.comGrupo:
                            if not i in j.alunosRepetem:
                                j.alunosRepetem.append(i)
                        else:
                            j.semGrupo.remove(i)
                            j.comGrupo.append(i)

                        #Para o loop que passa por todas as turmas
                        #É esperado que um aluno não esteja em mais de uma turma
                        break

                #Verifica se todos os membros do grupo existem
                existem = existem and existe

            #Se algum membro do grupo não existe o programa avisa
            if not existem:
                print('O grupo possuí algum aluno que não existe!')
                self.inexistentes.append(grupo)

            #Se o grupo possui membros de turmas diferentes o programa avisa
            if misto:
                print('Grupo composto por alunos de turmas diferentes!')
                self.mistos.append(grupo)

            #Caso nenhum membro do grupo pertença a alguma turma o programa avisa
            elif turma == 0:
                print('Nenhum membro do grupo existe!')

            #Caso todos os membros do grupo sejam de uma mesma turma, o programa avisa
            else:
                print('Grupo da turma {}!'.format(turma))
                self.turmas[turma - 1].numGrupos += 1
                self.turmas[turma - 1].grupos.append(grupo)

            #Adiciona o grupo à lista de grupos
            self.grupos.append(grupo)
        else:
            print('FALHA AO PROCESSAR O ARQUIVO DO GRUPO!\n')

trabalho = Trabalho(2)

while input("\nDeseja adicionar algum grupo? (s/n) ") != 'n':
    trabalho.novoGrupo(nomeArquivo = input("\nDigite o nome do arquivo do grupo: "))
print('')

print(trabalho, end = '')

input('Aperte ENTER para fechar o programa...')