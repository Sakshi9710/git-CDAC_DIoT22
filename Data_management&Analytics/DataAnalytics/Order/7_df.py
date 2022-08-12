#Display salesPerson located either in Barcelona or london
from pyspark.sql import SparkSession
spark = ( SparkSession.builder.appName("SparkSQL Demo").getOrCreate() )

csv_file= "salespeople.txt"

df = (spark.read.format("csv").option("inferSchema","true").option("header","true").load(csv_file))

df.createOrReplaceTempView("sales_tbl")

spark.sql("""Select sname,comm
        FROM sales_tbl
        WHERE city='Barcelona' or city='London'""").show()
        

#DATAFRAME CODE

df.select(['snum','city','comm']).filter(  (df['city']=='Barcelona') | (df['city']=='London') ).show()