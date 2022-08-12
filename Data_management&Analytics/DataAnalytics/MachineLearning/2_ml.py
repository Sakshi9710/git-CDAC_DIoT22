from pyspark.sql import SparkSession

from pyspark.ml.regression import LinearRegression
from pyspark.ml.linalg import Vectors
from pyspark.ml.feature import VectorAssembler

spark = SparkSession.builder.appName ('lr_example').getOrCreate ()

data = spark.read.csv ('Ecommerce_Customers.csv', inferSchema = True, header = True)

assembler = VectorAssembler (inputCols = ['Avg Session Length', 'Time on App', 'Time on Website', 'Length of Membership'], outputCol = 'features')

output = assembler.transform (data)

output.printSchema()

output.select('features').show()

print(output.head(1))