
from pyspark.sql.types import StructField,StringType,IntegerType,StructType
from pyspark.sql import SparkSession
spark = SparkSession.builder.appName('Basic').getOrCreate()

#Third Parameter indicates nulls allowed
data_schema = [StructField ('age',IntegerType(),True),
                StructField('name',StringType(),True)]

final_struct = StructType (fields = data_schema)

df = spark.read.json('people.json',schema = final_struct)
#To Print DataSet Schema
df.printSchema()