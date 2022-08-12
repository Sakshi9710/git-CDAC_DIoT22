from pyspark.sql import SparkSession
from pyspark.sql.functions import countDistinct , avg , count , min ,format_number

spark = SparkSession.builder.appName('Basic').getOrCreate()
df=spark.read.csv('sales_info-2.csv',inferSchema = True , header = True)

df.select(countDistinct('Sales')).show()

#Earlier Syntax
df.agg({'Sales':'sum'}).show()

#Another Syntax for the same thing
df.select(avg('Sales')).show()

df.select(min ('Sales')).show()

#Second Technique
sales_avg=df.select(avg('Sales').alias('tempvar'))

sales_avg.select (format_number('tempvar',2).alias('Average')).show()