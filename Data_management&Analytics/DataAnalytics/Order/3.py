#find all detail about Salespeople
#Do same Thing by using the * syntax

from pyspark.sql import SparkSession
spark = ( SparkSession.builder.appName("SparkSQL Demo").getOrCreate() )

csv_file= "salespeople.txt"

df = (spark.read.format("csv").option("inferSchema","true").option("header","true").load(csv_file))

df.createOrReplaceTempView("sales_tbl")

spark.sql("""Select snum,sname,city,comm
        FROM sales_tbl""").show()

spark.sql("""Select *
        FROM sales_tbl""").show()