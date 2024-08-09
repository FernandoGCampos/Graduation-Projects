import unicodedata

class Aluno:
    def __init__(self, num, nome):
        #Remove espaços e sublinhados (por mais que seja falha do usuário)
        if nome.startswith(' '):
            nome = nome.split(' ', 1)
            nome = nome[1]
        nome = nome.replace('_', ' ')

        #Remove caracteres especiais dos nomes, como acentos e ç
        #Possibilita comparar nomes de maneira mais fácil
        nome = unicodedata.normalize("NFKD", nome)
        nome = nome.encode("ascii", "ignore")
        nome = nome.decode("utf-8")

        #Salva o número e o nome
        self.num = num
        self.nome = nome

    def __str__(self):
        return '{},{}\n'.format(self.num, self.nome)

    #Utilizado para saber a qual turma o aluno pertence
    def __eq__(self, other):
        return self.num == other.num and self.nome == other.nome