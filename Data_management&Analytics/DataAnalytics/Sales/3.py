from pyspark.sql import SparkSession
spark = SparkSession.builder.appName('Basic').getOrCreate()
df=spark.read.csv('sales_info-2.csv',inferSchema = True , header = True)

group_data=df.groupby("Company")

group_data.agg({'Sales':'sum'}).show()