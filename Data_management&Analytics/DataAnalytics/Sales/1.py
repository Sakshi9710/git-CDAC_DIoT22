from pyspark.sql import SparkSession
spark = SparkSession.builder.appName('Basic').getOrCreate()
df=spark.read.csv('sales_info-2.csv',inferSchema = True , header = True)

df.groupby("Company").mean().show()

df.groupby("Company").sum().show()
df.groupby("Company").min().show()
df.groupby("Company").max().show()
df.groupby("Company").mean().show()