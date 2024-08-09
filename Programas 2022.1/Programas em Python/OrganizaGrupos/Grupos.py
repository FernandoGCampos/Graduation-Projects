import csv
from Alunos import Aluno

class Grupo:
    def __init__(self, nomeArquivo):
        try:
            #Abre o arquivo e passa todos os dados do .csv
            # enconding modificado para ele não alterar caracteres epeciais para mais de uma caractere (ex: 'ç' => 'Ã§')
            arquivo = open(nomeArquivo, 'r', encoding='utf-8')
            linhas = csv.reader(arquivo)

            #Le as linhas do arquivo
            self.membros = []
            for linha in linhas:
                self.membros.append( Aluno( linha[0],linha[1] ) )

            #Salva o tamanho do grupo
            self.tamanho = len(self.membros)

            #Indica que não ocorreu erros na leitura do arquivo
            self.existe = True
        except:
            # Indica que ocorreu erros na leitura do arquivo
            self.existe = False
        finally:
            # Fecha o arquivo independente de ter ocorrido um erro
            arquivo.close()

    def __str__(self):
        string = ''
        for i in self.membros:
            string += i.__str__()
        return string