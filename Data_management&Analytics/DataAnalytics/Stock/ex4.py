from pyspark.sql import SparkSession
spark = SparkSession.builder.appName('Basic').getOrCreate()
df=spark.read.csv('appl_stock.csv',inferSchema = True , header = True)

#collect () will store the result into a python list
filtered = df.filter (df["Low"]==197.16).collect()

print(filtered)