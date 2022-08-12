from pyspark.sql import SparkSession
from pyspark.sql.functions import avg

spark = (SparkSession
        .builder
        .appName ("AuthorAge")
        .getOrCreate())

data_df = spark.createDataFrame ([('Sachin',49),('Rahul',51),('MSD',40),('sunil',73),('Sachin',39),('Rahul',41),('MSD',30),('sunil',63)],["name","age"])

avg_df = data_df.groupBy ("name").agg (avg ("age"))

avg_df.show()