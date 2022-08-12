#Display customers whose rating is 100

from pyspark.sql import SparkSession
spark = ( SparkSession.builder.appName("SparkSQL Demo").getOrCreate() )

csv_file= "customers.txt"

df = (spark.read.format("csv").option("inferSchema","true").option("header","true").load(csv_file))

df.createOrReplaceTempView("customer_tbl")

spark.sql("""Select *
        FROM customer_tbl
        WHERE ranking==100""").show()

#DATAFRAME CODE

df.select(['cnum','cname','city','ranking','snum']).filter(df['ranking']==100).show()