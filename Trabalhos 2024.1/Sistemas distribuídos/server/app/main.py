from typing import Union, Annotated

from fastapi import FastAPI, Form

from pyspark.sql import SparkSession, DataFrame, DataFrameWriterV2
from pyspark.sql.types import *

from pydantic import BaseModel

import json

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

@app.get("/items")
def read_root():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", table_name)\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

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