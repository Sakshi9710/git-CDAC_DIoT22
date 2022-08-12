from pyspark.sql import SparkSession
spark = ( SparkSession.builder.appName("SparkSQL Demo").getOrCreate() )

csv_file= "appl_stock.csv"

df = (spark.read.format("csv").option("inferSchema","true").option("header","true").load(csv_file))

df.createOrReplaceTempView("stock_tbl")

spark.sql("""SELECT Date, Open , Close
        FROM stock_tbl
        WHERE Low==197.16""").show()