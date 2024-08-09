from pyspark.sql import SparkSession

spark = SparkSession.builder\
        .master('spark://localhost:7077')\
        .appName('teste')\
        .config("spark.jars", "jars/postgresql-42.7.3.jar")\
        .getOrCreate()\

url = "jdbc:postgresql://localhost:5444/scd"

properties = {
    "user": "scd",
    "password": "scd",
    "driver": "org.postgresql.Driver"
}

table_name = "teste"

df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", table_name)\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
print(df)