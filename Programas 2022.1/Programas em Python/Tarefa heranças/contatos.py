class Contato:
    def __init__(self, _nome = '', _endereco = '', _email = '', _tipo = 0):
        self.nome = _nome
        self.endereco = _endereco
        self.email = _email
        self.tipo = _tipo

    def __str__(self):
        string = 'Nome: {}\n'.format(self.nome)
        string += 'Endereco: {}\n'.format(self.endereco)
        string += 'E-mail: {}\n'.format(self.email)

        return string


class pessoaFisica(Contato):
    def __init__(self, _cpf = "", _nascimento = "", _estadoCivil = "", **kwargs):
        super().__init__(**kwargs, _tipo = 1)
        self.cpf = _cpf
        self.nascimento = _nascimento
        self.estadoCivil = _estadoCivil

    def __str__(self):
        string = super().__str__()
        string += 'CPF: {}\n'.format(self.cpf)
        string += 'Nascimento: {}\n'.format(self.nascimento)
        string += 'Estado civil: {}\n'.format(self.estadoCivil)

        return string


class pessoaJuridica(Contato):
    def __init__(self, _cnpj = '', _inscricaoEstadual = '', _razaoSocial = '', **kwargs):
        super().__init__(**kwargs, _tipo = 2)
        self.cnpj = _cnpj
        self.inscricaoEstadual = _inscricaoEstadual
        self.razaoSocial = _razaoSocial

    def __str__(self):
        string = super().__str__()
        string += 'CNPJ: {}\n'.format(self.cnpj)
        string += 'Inscricao estadual: {}\n'.format(self.inscricaoEstadual)
        string += 'Razao social: {}\n'.format(self.razaoSocial)

        return string