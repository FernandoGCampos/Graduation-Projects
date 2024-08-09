from typing import Union, Annotated

from utils.schema import *

from fastapi import FastAPI, Form, HTTPException

from pyspark.sql import SparkSession, DataFrame, DataFrameWriterV2
from pyspark.sql.types import *

import json

from utils.schema import *

spark = SparkSession.Builder()\
        .master('spark://spark:7077')\
        .appName('teste')\
        .config("spark.jars", "/code/app/jars/postgresql-42.7.3.jar")\
        .getOrCreate()\

url = "jdbc:postgresql://db:5432/scd"

properties = {
    "user": "scd",
    "password": "scd",
    "driver": "org.postgresql.Driver"
}

table_name = "teste"

app = FastAPI()

@app.get("/")
def read_root():
    return {
        "Hello": "World"
    }

@app.get("/ativo/")
def read_ativo():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "ativo")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/ativo/")
def add_ativo(data: ativoData):
    try:
        df: DataFrame = spark.createDataFrame([data], ativoSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "ativo", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"nome": data.nome}

@app.get("/ativoremedio/")
def read_ativoremedio():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "ativoremedio")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/ativoremedio/")
def add_ativoremedio(data: ativoremedioData):
    try:
        df: DataFrame = spark.createDataFrame([data], ativoremedioSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "ativoremedio", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {data}

@app.get("/estoquelocal/")
def read_estoquelocal():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "estoquelocal")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/estoquelocal/")
def add_estoquelocal(data: estoquelocalData):
    try:
        df: DataFrame = spark.createDataFrame([data], estoquelocalSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "estoquelocal", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.get("/estoquelocalremedio/")
def read_estoquelocalremedio():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "estoquelocalremedio")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/estoquelocalremedio/")
def add_estoquelocalremedio(data: estoquelocalremedioData):
    try:
        df: DataFrame = spark.createDataFrame([data], estoquelocalremedioSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "estoquelocalremedio", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.get("/estoqueregional/")
def read_estoqueregional():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "estoqueregional")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/estoqueregional/")
def add_estoqueregional(data: estoqueregionalData):
    try:
        df: DataFrame = spark.createDataFrame([data], estoqueregionalSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "estoqueregional", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.get("/estoqueregionalremedio/")
def read_estoqueregionalremedio():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "estoqueregionalremedio")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/estoqueregionalremedio/")
def add_estoqueregionalremedio(data: estoqueregionalremedioData):
    try:
        df: DataFrame = spark.createDataFrame([data], estoqueregionalremedioSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "estoqueregionalremedio", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.get("/farmaceutico/")
def read_farmaceutico():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "farmaceutico")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/farmaceutico/")
def add_farmaceutico(data: farmaceuticoData):
    try:
        df: DataFrame = spark.createDataFrame([data], farmaceuticoSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "farmaceutico", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.get("/medico/")
def read_medico():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "medico")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/medico/")
def add_medico(data: medicoData):
    try:
        df: DataFrame = spark.createDataFrame([data], medicoSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "medico", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.get("/paciente/")
def read_paciente():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "paciente")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/paciente/")
def add_paciente(data: pacienteData):
    try:
        df: DataFrame = spark.createDataFrame([data], pacienteSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "paciente", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.get("/posto/")
def read_posto():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "posto")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/posto/")
def add_posto(data: postoData):
    try:
        df: DataFrame = spark.createDataFrame([data], postoSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "posto", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.get("/receita/")
def read_receita():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "receita")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/receita/")
def add_receita(data: receitaData):
    try:
        df: DataFrame = spark.createDataFrame([data], receitaSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "receita", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.get("/receitaremedio/")
def read_receitaremedio():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "receitaremedio")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/receitaremedio/")
def add_receitaremedio(data: receitaremedioData):
    try:
        df: DataFrame = spark.createDataFrame([data], receitaremedioSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "receitaremedio", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.get("/regiao/")
def read_regiao():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "regiao")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/regiao/")
def add_regiao(data: regiaoData):
    try:
        df: DataFrame = spark.createDataFrame([data], regiaoSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "regiao", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.get("/remedio/")
def read_remedio():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "remedio")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/remedio/")
def add_remedio(data: remedioData):
    try:
        df: DataFrame = spark.createDataFrame([data], remedioSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "remedio", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.get("/tarja/")
def read_tarja():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "tarja")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/tarja/")
def add_tarja(data: tarjaData):
    try:
        df: DataFrame = spark.createDataFrame([data], tarjaSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "tarja", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.get("/usuario/")
def read_usuario():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "usuario")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/usuario/")
def add_usuario(data: usuarioData):
    try:
        df: DataFrame = spark.createDataFrame([data], usuarioSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "usuario", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

class TesteData(BaseModel):
    nome: str
    sobrenome: str

@app.post("/items/")
def add_item(data: TesteData):
    df: DataFrame = spark.createDataFrame([{"nome": data.nome, "sobrenome": data.sobrenome}], testeSchema)
    df.write.option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .jdbc(url, table_name, mode="append")
    return {"nome": data.nome, "sobrenome": data.sobrenome}


@app.post("/update/{item_id}")
def update_item(item_id: int, data: TesteData):
    df: DataFrame = spark.createDataFrame([{"id": item_id, "nome": data.nome, "sobrenome": data.sobrenome}], testeSchemaUpdate)
    df.write.option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .jdbc(url, table_name, mode="append")
    return {"nome": data.nome, "sobrenome": data.sobrenome}


@app.get("/items/{item_id}")
def read_item(item_id: int, q: Union[str, None] = None):
    return {"item_id": item_id, "q": q}


@app.get("/remedio/{nome}")
def read_remedio_nome(nome: str):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM remedio WHERE NOME ILIKE '%{nome}%'")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/receita/{id}")
def read_receita(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM receita WHERE ID = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/receitaremedio/{id}")
def read_receitaremedio(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM receitaremedio WHERE receita = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/usuario/{cpf}")
def read_usuario(cpf: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM usuario WHERE CPF = '{cpf}'")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/farmaceutico/{cpf}")
def read_farmaceutico(cpf: str):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM farmaceutico WHERE usuario = '{cpf}'")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/medico/{cpf}")
def read_medico(cpf: str):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM medico WHERE usuario = '{cpf}'")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/paciente/{cpf}")
def read_paciente(cpf: str):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM paciente WHERE usuario = '{cpf}'")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/regiao/{id}")
def read_regiao(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM regiao WHERE ID = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/tarja/{nome}")
def read_tarja_nome(nome: str):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM tarja WHERE NOME ILIKE '%{nome}%'")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/posto/{id}")
def read_posto(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM posto WHERE ID = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/estoqueregional/{id}")
def read_estoqueregional(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM estoqueregional WHERE ID = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/estoqueregionalremedio/{id}")
def read_estoqueregionalremedio(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM estoqueregionalremedio WHERE estoqueregional = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/estoquelocal/{id}")
def read_estoquelocal(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM estoquelocal WHERE ID = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/estoquelocalremedio/{id}")
def read_estoquelocalremedio(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM estoquelocalremedio WHERE estoquelocal = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()