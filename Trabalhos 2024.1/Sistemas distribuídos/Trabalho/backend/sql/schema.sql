-- Cria uma sequência para gerar IDs únicos para a tabela regiao
CREATE SEQUENCE regiao_id_seq START 1 AS bigint;

-- Cria a tabela regiao para armazenar informações sobre as regiões
CREATE TABLE regiao (
    id bigint NOT NULL default nextval('regiao_id_seq'), -- ID único para a região
    nome varchar(64) NOT NULL, -- Nome da região
    CONSTRAINT pk_regiao PRIMARY KEY(id) -- Chave primária da tabela
);

-- Altera a propriedade da sequência para ser propriedade da coluna ID da tabela regiao
ALTER SEQUENCE regiao_id_seq OWNED BY regiao.id;

-- Cria uma sequência para gerar IDs únicos para a tabela estoqueregional
CREATE SEQUENCE estoqueregional_id_seq START 1 AS bigint;

-- Cria a tabela estoqueregional para armazenar informações sobre o estoque em nível regional
CREATE TABLE estoqueregional (
    id bigint NOT NULL default nextval('estoqueregional_id_seq'), -- ID único para o estoque regional
    regiao bigint NOT NULL, -- Referência à região
    CONSTRAINT pk_estoqueregional PRIMARY KEY(id), -- Chave primária da tabela
    CONSTRAINT fk_estoqueregional_regiao FOREIGN KEY(regiao) REFERENCES regiao (id) ON DELETE CASCADE ON UPDATE CASCADE -- Restrição de chave estrangeira para garantir integridade referencial
);

-- Altera a propriedade da sequência para ser propriedade da coluna ID da tabela estoqueregional
ALTER SEQUENCE estoqueregional_id_seq OWNED BY estoqueregional.id;

-- Cria uma sequência para gerar IDs únicos para a tabela estoquelocal
CREATE SEQUENCE estoquelocal_id_seq START 1 AS bigint;

-- Cria a tabela estoquelocal para armazenar informações sobre o estoque em nível local
CREATE TABLE estoquelocal (
    id bigint NOT NULL default nextval('estoquelocal_id_seq'), -- ID único para o estoque local
    regiao bigint NOT NULL, -- Referência à região
    CONSTRAINT pk_estoquelocal PRIMARY KEY (id), -- Chave primária da tabela
    CONSTRAINT fk_estoquelocal_regiao FOREIGN KEY(regiao) REFERENCES regiao(id) ON DELETE CASCADE ON UPDATE CASCADE -- Restrição de chave estrangeira para garantir integridade referencial
);

-- Altera a propriedade da sequência para ser propriedade da coluna ID da tabela estoquelocal
ALTER SEQUENCE estoquelocal_id_seq OWNED BY estoquelocal.id;

-- Cria a tabela tarja para armazenar informações sobre as tarjas dos medicamentos
CREATE TABLE tarja (
    nome varchar(64) NOT NULL, -- Nome da tarja
    retencao bool NOT NULL DEFAULT false, -- Indica se a tarja requer retenção
    CONSTRAINT pk_tarja PRIMARY KEY(nome) -- Chave primária da tabela
);

-- Cria a tabela remedio para armazenar informações sobre os medicamentos
CREATE TABLE remedio(
    nome varchar(256) NOT NULL, -- Nome do medicamento
    tarja varchar(64) NOT NULL, -- Referência à tarja do medicamento
    CONSTRAINT pk_remedio PRIMARY KEY(nome), -- Chave primária da tabela
    CONSTRAINT fk_remedio_tarja FOREIGN KEY(tarja) REFERENCES tarja(nome) ON DELETE CASCADE ON UPDATE CASCADE -- Restrição de chave estrangeira para garantir integridade referencial
);

-- Cria a tabela ativo para armazenar informações sobre os principios ativos
CREATE TABLE ativo(
    nome varchar(256) NOT NULL, -- Nome do ativo
    constraint pk_ativo PRIMARY KEY(nome) -- Chave primária da tabela
);

-- Cria a tabela ativoremedio para armazenar informações sobre os principios ativos de cada remedio
CREATE TABLE ativoremedio(
    remedio varchar(256) NOT NULL, -- Referência ao remédio
    ativo varchar(256) NOT NULL, -- Referência ao principio ativo
    CONSTRAINT pk_ativoremedio PRIMARY KEY(remedio, ativo), -- Chave primária da tabela
	CONSTRAINT fk_ativoremedio_at FOREIGN KEY(ativo) REFERENCES ativo(nome) ON DELETE CASCADE ON UPDATE CASCADE, --Restrição de chave estrangeira para garantir integridade referencial
	CONSTRAINT fk_ativoremedio_rem FOREIGN KEY(remedio) REFERENCES remedio(nome) ON DELETE CASCADE ON UPDATE CASCADE --Restrição de chave estrangeira para garantir integridade referencial
);

-- Cria a tabela estoquelocalremedio para relacionar medicamentos aos estoques locais
CREATE TABLE estoquelocalremedio (
    estoquelocal bigint NOT NULL, -- Referência ao estoque local
    remedio varchar(256) NOT NULL, -- Referência ao medicamento
    quantidade bigint NOT NULL, -- Quantidade do medicamento no estoque local
    CONSTRAINT pk_estoquelocalremedio PRIMARY KEY(estoquelocal, remedio), -- Chave primária da tabela
    CONSTRAINT fk_estoquelocalremedio_el FOREIGN KEY(estoquelocal) REFERENCES estoquelocal(id) ON DELETE CASCADE ON UPDATE CASCADE, -- Restrição de chave estrangeira para garantir integridade referencial
    CONSTRAINT fk_estoquelocalremedio_rem FOREIGN KEY(remedio) REFERENCES remedio(nome) ON DELETE CASCADE ON UPDATE CASCADE -- Restrição de chave estrangeira para garantir integridade referencial
);

-- Cria a tabela estoqueregionalremedio para relacionar medicamentos aos estoques regionais
CREATE TABLE estoqueregionalremedio (
    estoqueregional bigint NOT NULL, -- Referência ao estoque regional
    remedio varchar(256) NOT NULL, -- Referência ao medicamento
    quantidade bigint NOT NULL, -- Quantidade do medicamento no estoque regional
    CONSTRAINT pk_estoqueregionalremedio PRIMARY KEY(estoqueregional, remedio), -- Chave primária da tabela
    CONSTRAINT fk_estoqueregionalremedio_el FOREIGN KEY(estoqueregional) REFERENCES estoqueregional(id) ON DELETE CASCADE ON UPDATE CASCADE, -- Restrição de chave estrangeira para garantir integridade referencial
    CONSTRAINT fk_estoqueregionalremedio_rem FOREIGN KEY(remedio) REFERENCES remedio(nome) ON DELETE CASCADE ON UPDATE CASCADE -- Restrição de chave estrangeira para garantir integridade referencial
);

-- Cria uma sequência para gerar IDs únicos para a tabela posto
CREATE SEQUENCE posto_id_seq START 1 AS bigint;

-- Cria a tabela posto para representar os postos de atendimento
CREATE TABLE posto (
    id bigint NOT NULL default nextval('posto_id_seq'), -- ID único para o posto
    nome varchar(256) NOT NULL, -- Nome do posto
    regiao bigint NOT NULL, -- Referência à região
    CONSTRAINT pk_posto PRIMARY KEY(id), -- Chave primária da tabela
    CONSTRAINT fk_posto_regiao FOREIGN KEY(regiao) REFERENCES regiao(id) ON DELETE CASCADE ON UPDATE CASCADE -- Restrição de chave estrangeira para garantir integridade referencial
);

-- Altera a propriedade da sequência para ser propriedade da coluna ID da tabela posto
ALTER SEQUENCE posto_id_seq OWNED BY posto.id;

-- Cria a tabela usuario para armazenar informações sobre os usuários do sistema
CREATE TABLE usuario (
    cpf varchar(12) NOT NULL, -- CPF do usuário
    senha varchar(144) NOT NULL, -- Senha do usuário
    email varchar(240) NOT NULL, -- Endereço de email do usuário
    CONSTRAINT pk_usuario PRIMARY KEY(cpf), -- Chave primária da tabela
    CONSTRAINT ck_proper_email CHECK ( -- Restrição para garantir formato adequado do endereço de email
        email IS NULL
        OR email ~* '^[A-Za-z0-9._+%-]+@[A-Za-z0-9.-]+[.][A-Za-z]+$'
    )
);

-- Cria a tabela farmaceutico para representar os farmacêuticos do sistema
CREATE TABLE farmaceutico (
    usuario varchar(12) NOT NULL, -- Referência ao usuário
    posto bigint NOT NULL, -- Referência ao posto onde o farmacêutico trabalha
    CONSTRAINT pk_farmaceutico PRIMARY KEY(usuario), -- Chave primária da tabela
    CONSTRAINT fk_farmaceutico_usuario FOREIGN KEY(usuario) REFERENCES usuario(cpf) ON DELETE CASCADE ON UPDATE CASCADE, -- Restrição de chave estrangeira para garantir integridade referencial
    CONSTRAINT fk_farmaceutico_posto FOREIGN KEY(posto) REFERENCES posto(id) ON DELETE CASCADE ON UPDATE CASCADE -- Restrição de chave estrangeira para garantir integridade referencial
);

-- Cria a tabela medico para representar os médicos do sistema
CREATE TABLE medico (
    usuario varchar(12) NOT NULL, -- Referência ao usuário
    posto bigint NOT NULL, -- Referência ao posto onde o médico atende
    CONSTRAINT pk_medico PRIMARY KEY(usuario), -- Chave primária da tabela
    CONSTRAINT fk_medico_usuario FOREIGN KEY(usuario) REFERENCES usuario(cpf) ON DELETE CASCADE ON UPDATE CASCADE, -- Restrição de chave estrangeira para garantir integridade referencial
    CONSTRAINT fk_medico_posto FOREIGN KEY(posto) REFERENCES posto(id) ON DELETE CASCADE ON UPDATE CASCADE -- Restrição de chave estrangeira para garantir integridade referencial
);

-- Cria a tabela paciente para representar os pacientes do sistema
CREATE TABLE paciente (
    usuario varchar(12) NOT NULL, -- Referência ao usuário
    convenio varchar(240) NOT NULL, -- Plano de saúde do paciente
    posto bigint NOT NULL, -- Referência ao posto de atendimento do paciente
    CONSTRAINT pk_paciente PRIMARY KEY(usuario), -- Chave primária da tabela
    CONSTRAINT fk_paciente_usuario FOREIGN KEY(usuario) REFERENCES usuario(cpf) ON DELETE CASCADE ON UPDATE CASCADE, -- Restrição de chave estrangeira para garantir integridade referencial
    CONSTRAINT fk_paciente_posto FOREIGN KEY(posto) REFERENCES posto(id) ON DELETE CASCADE ON UPDATE CASCADE -- Restrição de chave estrangeira para garantir integridade referencial
);

-- Cria uma sequência para gerar IDs únicos para a tabela receita
CREATE SEQUENCE receita_id_seq START 1 AS bigint;

-- Cria a tabela receita para representar as receitas médicas
CREATE TABLE receita (
    id bigint NOT NULL default nextval('receita_id_seq'), -- ID único para a receita
    medico varchar(12) NOT NULL, -- Referência ao médico que emitiu a receita
    paciente varchar(12) NOT NULL, -- Referência ao paciente para quem a receita foi emitida
    posto bigint NOT NULL, -- Referência ao posto onde a receita foi emitida
    CONSTRAINT pk_receita PRIMARY KEY(id), -- Chave primária da tabela
    CONSTRAINT fk_receita_medico FOREIGN KEY(medico) REFERENCES medico(usuario) ON DELETE CASCADE ON UPDATE CASCADE, -- Restrição de chave estrangeira para garantir integridade referencial
    CONSTRAINT fk_receita_paciente FOREIGN KEY(paciente) REFERENCES paciente(usuario) ON DELETE CASCADE ON UPDATE CASCADE, -- Restrição de chave estrangeira para garantir integridade referencial
    CONSTRAINT fk_receita_posto FOREIGN KEY(posto) REFERENCES posto(id) ON DELETE CASCADE ON UPDATE CASCADE -- Restrição de chave estrangeira para garantir integridade referencial
);

-- Altera a propriedade da sequência para ser propriedade da coluna ID da tabela receita
ALTER SEQUENCE receita_id_seq OWNED BY receita.id;

-- Cria a tabela receitaremedio para associar medicamentos às receitas
CREATE TABLE receitaremedio (
    receita bigint NOT NULL, -- Referência à receita
    remedio varchar(256) NOT NULL, -- Referência ao medicamento prescrito na receita
    prontidao char(1) NOT NULL, -- Indica a prontidão do medicamento ('E' = em uso, 'S' = sob demanda, 'M' = para mais tarde)
    CONSTRAINT pk_receitaremedio PRIMARY KEY(receita, remedio), -- Chave primária da tabela
    CONSTRAINT fk_receitaremedio_receita FOREIGN KEY(receita) REFERENCES receita(id) ON DELETE CASCADE ON UPDATE CASCADE, -- Restrição de chave estrangeira para garantir integridade referencial
    CONSTRAINT fk_receitaremedio_remedio FOREIGN KEY(remedio) REFERENCES remedio(nome) ON DELETE CASCADE ON UPDATE CASCADE, -- Restrição de chave estrangeira para garantir integridade referencial
    CONSTRAINT ck_prontidao CHECK (prontidao IN ('E', 'S', 'M')) -- Restrição para garantir que prontidao seja 'E', 'S' ou 'M'
);