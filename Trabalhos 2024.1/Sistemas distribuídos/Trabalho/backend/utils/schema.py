from pyspark.sql.types import *
from pydantic import BaseModel

# Schema definition for the Kafka JSON payload
testeFields = [
    StructField("customerId", StringType()),
    StructField("customerFName", StringType()),
    StructField("customerLName", StringType()),
    StructField("customerEmail", StringType()),
    StructField("customerPassword", StringType()),
    StructField("customerStreet", StringType()),
    StructField("customerCity", StringType()),
    StructField("customerState", StringType()),
    StructField("customerZipcode", StringType())
]

testeSchema = StructType([
    StructField("nome", StringType()),
    StructField("sobrenome", StringType())
])

testeSchemaUpdate = StructType([
    StructField("id", IntegerType()),
    StructField("nome", StringType()),
    StructField("sobrenome", StringType())
])

regiaoSchema = StructType([
    StructField("nome", StringType())
])

estoqueregionalSchema = StructType([
    StructField("regiao", IntegerType())
])

estoquelocalSchema = StructType([
    StructField("regiao", IntegerType())
])

tarjaSchema = StructType([
    StructField("nome", StringType()),
    StructField("retencao", BooleanType())
])

remedioSchema = StructType([
    StructField("nome", StringType()),
    StructField("tarja", StringType())
])

# Schema para a tabela "ativo"
ativoSchema = StructType([
    StructField("nome", StringType())
])

# Schema para a tabela "ativoremedio"
ativoremedioSchema = StructType([
    StructField("remedio", StringType()),
    StructField("ativo", StringType())
])

# Schema para a tabela "estoqueregionalremedio"
estoqueregionalremedioSchema = StructType([
    StructField("estoqueregional", LongType()),
    StructField("remedio", StringType()),
    StructField("quantidade", LongType())
])

# Schema para a tabela "estoquelocalremedio"
estoquelocalremedioSchema = StructType([
    StructField("estoquelocal", LongType()),
    StructField("remedio", StringType()),
    StructField("quantidade", LongType())
])

# Schema para a tabela "posto"
postoSchema = StructType([
    StructField("nome", StringType()),
    StructField("regiao", LongType())
])

# Schema para a tabela "usuario"
usuarioSchema = StructType([
    StructField("cpf", StringType()),
    StructField("senha", StringType()),
    StructField("email", StringType())
])

# Schema para a tabela "farmaceutico"
farmaceuticoSchema = StructType([
    StructField("usuario", StringType()),
    StructField("posto", LongType())
])

# Schema para a tabela "medico"
medicoSchema = StructType([
    StructField("usuario", StringType()),
    StructField("posto", LongType())
])

# Schema para a tabela "paciente"
pacienteSchema = StructType([
    StructField("usuario", StringType()),
    StructField("convenio", StringType()),
    StructField("posto", LongType())
])

# Schema para a tabela "receita"
receitaSchema = StructType([
    StructField("medico", StringType()),
    StructField("paciente", StringType()),
    StructField("posto", LongType())
])

# Schema para a tabela "receitaremedio"
receitaremedioSchema = StructType([
    StructField("receita", LongType()),
    StructField("remedio", StringType()),
    StructField("prontidao", CharType(1))
])

class regiaoData(BaseModel):
    nome: str

class estoqueregionalData(BaseModel):
    regiao: int

class estoquelocalData(BaseModel):
    regiao: int

class tarjaData(BaseModel):
    nome: str
    retencao: bool

class remedioData(BaseModel):
    nome: str
    tarja: str

class ativoData(BaseModel):
    nome: str

class ativoremedioData(BaseModel):
    remedio: str
    ativo: str

class estoqueregionalremedioData(BaseModel):
    estoqueregional: int
    remedio: str
    quantidade: int

class estoquelocalremedioData(BaseModel):
    estoquelocal: int
    remedio: str
    quantidade: int

class postoData(BaseModel):
    nome: str
    regiao: int

class usuarioData(BaseModel):
    cpf: str
    senha: str
    email: str

class farmaceuticoData(BaseModel):
    usuario: str
    posto: int

class medicoData(BaseModel):
    usuario: str
    posto: int

class pacienteData(BaseModel):
    usuario: str
    convenio: str
    posto: int

class receitaData(BaseModel):
    medico: str
    paciente: str
    posto: int

class receitaremedioData(BaseModel):
    receita: int
    remedio: str
    prontidao: str
    
