from pyspark.sql import SparkSession
spark = ( SparkSession.builder.appName("SparkSQL Demo").getOrCreate() )

csv_file= "sales_info-2.csv"

df = (spark.read.format("csv").option("inferSchema","true").option("header","true").load(csv_file))

df.createOrReplaceTempView("sales_tbl")

spark.sql("""SELECT Company, sum(Sales) SUM,avg(Sales) MEAN , min(Sales) MIN , max(Sales) Max
        FROM sales_tbl
        GROUP BY Company""").show()