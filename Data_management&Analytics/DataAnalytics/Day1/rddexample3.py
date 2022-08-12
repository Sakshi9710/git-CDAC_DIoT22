from pyspark.sql import SparkSession

spark = (SparkSession
        .builder
        .appName ("test")
        .getOrCreate()
        )

strings = spark.read.text("text.txt")
filtered = strings.filter(strings.value.contains("Spark"))
output=filtered.count()

print("Number of rows that include the keyword: %d" % output)