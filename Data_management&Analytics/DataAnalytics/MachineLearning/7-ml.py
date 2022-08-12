from pyspark.sql import SparkSession

from pyspark.ml.regression import LinearRegression
from pyspark.ml.linalg import Vectors
from pyspark.ml.feature import VectorAssembler

spark = SparkSession.builder.appName ('lr_example').getOrCreate ()

data = spark.read.csv ('Ecommerce_Customers.csv', inferSchema = True, header = True)

assembler = VectorAssembler (inputCols = ['Avg Session Length', 'Time on App', 'Time on Website', 'Length of Membership'], outputCol = 'features')

output = assembler.transform (data)

final_data = output.select ('features', 'Yearly Amount Spent')

train_data, test_data = final_data.randomSplit ([0.7, 0.3])

lr = LinearRegression (labelCol = 'Yearly Amount Spent')

lr_model = lr.fit (train_data)

from pyspark.sql import SparkSession

from pyspark.ml.regression import LinearRegression
from pyspark.ml.linalg import Vectors
from pyspark.ml.feature import VectorAssembler

spark = SparkSession.builder.appName ('lr_example').getOrCreate ()

data = spark.read.csv ('Ecommerce_Customers.csv', inferSchema = True, header = True)

assembler = VectorAssembler (inputCols = ['Avg Session Length', 'Time on App', 'Time on Website', 'Length of Membership'], outputCol = 'features')

output = assembler.transform (data)

final_data = output.select ('features', 'Yearly Amount Spent')

train_data, test_data = final_data.randomSplit ([0.7, 0.3])

lr = LinearRegression (labelCol = 'Yearly Amount Spent')

lr_model = lr.fit (train_data)

test_results = lr_model.transform (test_data)

test_results.show ()