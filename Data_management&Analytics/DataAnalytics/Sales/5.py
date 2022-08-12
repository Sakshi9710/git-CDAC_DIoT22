from pyspark.sql import SparkSession
from pyspark.sql.functions import col

spark = SparkSession.builder.appName('Basic').getOrCreate()
df=spark.read.csv('sales_info-2.csv',inferSchema = True , header = True)

df.orderBy('Sales').show()

#only asc
df.orderBy('Sales').show()

#Better Syntax
df.orderBy(df['Sales'].asc()).show()

df.orderBy(df['Sales'].desc()).show()

#Another Syntax
df.orderBy(col('Sales').asc()).show()

df.orderBy(col('Sales').desc()).show()