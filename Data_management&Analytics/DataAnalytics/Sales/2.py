from pyspark.sql import SparkSession
spark = SparkSession.builder.appName('Basic').getOrCreate()
df=spark.read.csv('sales_info-2.csv',inferSchema = True , header = True)

df.agg({'Sales':'sum'}).show()

df.agg({'Sales':'min'}).show()
df.agg({'Sales':'max'}).show()
df.agg({'Sales':'count'}).show()
df.agg({'Sales':'mean'}).show()