import csv
from Alunos import Aluno
from Grupos import Grupo

class Turma:
    def __init__(self, nomeArquivo):
        try:
            # Abre o arquivo e passa todos os dados do .csv
            # enconding modificado para ele não alterar caracteres epeciais para mais de uma caractere (ex: 'ç' => 'Ã§')
            arquivo = open(nomeArquivo, 'r', encoding='utf-8')
            linhas = csv.reader(arquivo)

            #Le todas as linhas do arquivo.csv
            self.alunos = []
            for linha in linhas:
                self.alunos.append( Aluno( linha[0], linha[1] ) )

            #Salva o número de alunos
            self.numero = len(self.alunos)

            #Determina quais alunos já tem grupo e quais não tem
            self.semGrupo = self.alunos.copy()
            self.comGrupo = []

            #Salva os grupos da turma
            self.numGrupos = 0
            self.grupos = []

            #Guarda o nome de alunos que estão em mais de um grupo
            self.alunosRepetem = []

            ##Indica que não ocorreu erros na leitura do arquivo
            self.existe = True
        except:
             ##Indica que ocorreu erros na leitura do arquivo
             self.existe = False
        finally:
            #Fecha o arquivo independente de ter ocorrido um erro
            arquivo.close()

    def __str__(self):
        string = ''
        for i in self.alunos:
            string += i.__str__()
        return string