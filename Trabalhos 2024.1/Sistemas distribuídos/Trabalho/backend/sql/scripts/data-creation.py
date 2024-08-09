# necessaria a instalacao das duas bibliotecas
import pandas as pd
from unidecode import unidecode

# nome do arquivo com os remedios
filename = 'remedios_ativos.xls'

# leitura do dataframe
df = pd.read_excel(filename)
df = df.rename({'SUBSTÂNCIA': 'SUBSTANCIA'}, axis=1)
# mantendo apenas as colunas necessarias
df = df[['SUBSTANCIA', 'PRODUTO', 'TARJA']]

# removendo acentos
for col in ['SUBSTANCIA', 'PRODUTO', 'TARJA']:
    df[col] = df[col].apply(unidecode)

# encontrando os valores únicos de remedios, ativos e tarja
df_subs = df.drop_duplicates(subset=['SUBSTANCIA'])
df_prods = df.drop_duplicates(subset=['PRODUTO'])
df_tarjas = df.drop_duplicates(subset=['TARJA'])

commands = []

# Inserindo manualmente as tarjas, pois nao ha informacao da retencao
commands.append(f"INSERT INTO tarja(nome, retencao) VALUES ($$- (*) $$, false);")
commands.append(f"INSERT INTO tarja(nome, retencao) VALUES ($$Tarja Vermelha$$, false);")
commands.append(f"INSERT INTO tarja(nome, retencao) VALUES ($$Tarja Vermelha sob restricao$$, true);")
commands.append(f"INSERT INTO tarja(nome, retencao) VALUES ($$Tarja Sem Tarja$$, false);")
commands.append(f"INSERT INTO tarja(nome, retencao) VALUES ($$Tarja Preta$$, true);")

# Salvando principios ativos unicos
ativos = {}
id = 1

for line in df_subs['SUBSTANCIA']:
    valores = line.split(';')
    for valor in valores:
        if valor not in ativos:
            ativos[valor] = id
            id += 1
            
for ativo in ativos:
    new_insert = f"INSERT INTO ativo(nome) VALUES ($$" + ativo + f"$$);"
    commands.append(new_insert)


# Salvando os remedios e sua respectiva tarja
produtos = {}

for index, row in df_prods.iterrows():
    valor = row['PRODUTO']
    tarja = row['TARJA']
    if valor not in produtos:
        produtos[valor] = tarja            

# Inserindo remedios
for produto, tarja in produtos.items():
    new_insert = f"INSERT INTO remedio(nome, tarja) VALUES ($$" + produto + f"$$, $$" + tarja + f"$$);"
    commands.append(new_insert)

# Inserindo ativos de cada remedio
for produto, i in produtos.items():
    produto_ativo = []
    produto_ativo.append(df_prods.loc[df_prods["PRODUTO"] == produto])
    for ativo in produto_ativo:
        tmp = ativo.iloc[0]['SUBSTANCIA'].split(';')
        my_dict = {element: index for index, element in enumerate(tmp)}
        for value in my_dict:
            new_insert = f"INSERT INTO ativoremedio(remedio, ativo) VALUES ($$" + produto + f"$$, $$" + value + f"$$);"
            commands.append(new_insert)

# Salvando arquivo
sample_filename = 'sample-data.sql'

file = open(sample_filename, 'w')

for i in range(len(commands)):
    file.write(commands[i] + '\n')

file.close()