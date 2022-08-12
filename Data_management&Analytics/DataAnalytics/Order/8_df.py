#Display salesPerson who earn commision in the range of .10 and .12
from pyspark.sql import SparkSession
spark = ( SparkSession.builder.appName("SparkSQL Demo").getOrCreate() )

csv_file= "salespeople.txt"

df = (spark.read.format("csv").option("inferSchema","true").option("header","true").load(csv_file))

df.createOrReplaceTempView("sales_tbl")

spark.sql("""Select sname,comm
        FROM sales_tbl
        WHERE comm>=.10 and comm<=.12""").show()
        

#DATAFRAME CODE

df.select(['snum','city','comm']).filter(  (df['comm']>=.10) & (df['comm']<=.12) ).show()