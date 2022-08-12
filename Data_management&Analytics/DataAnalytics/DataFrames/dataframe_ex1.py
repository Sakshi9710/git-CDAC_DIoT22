from pyspark.sql import SparkSession
spark = SparkSession.builder.appName('Basic').getOrCreate()
df=spark.read.json('people.json')
#df.show()
#To Print DataSet Schema
df.printSchema()
#To See The Columns
print(df.columns)
#
print(df.describe)
#To see a statistical summary
print(df.describe().show())