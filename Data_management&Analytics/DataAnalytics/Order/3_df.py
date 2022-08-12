#Show only the salespeople name and commission
from pyspark.sql import SparkSession
spark = ( SparkSession.builder.appName("SparkSQL Demo").getOrCreate() )

csv_file= "salespeople.txt"

df = (spark.read.format("csv").option("inferSchema","true").option("header","true").load(csv_file))

df.createOrReplaceTempView("sales_tbl")

spark.sql("""Select sname,comm
        FROM sales_tbl""").show()
        

#DATAFRAME CODE

df.select(['snum','city','comm']).show()
