#Display all the Customer in San Jose whose Rating is above 200

from pyspark.sql import SparkSession
spark = ( SparkSession.builder.appName("SparkSQL Demo").getOrCreate() )

csv_file= "customers.txt"

df = (spark.read.format("csv").option("inferSchema","true").option("header","true").load(csv_file))

df.createOrReplaceTempView("customer_tbl")

spark.sql("""Select *
        FROM customer_tbl
        WHERE ranking>200 AND city='San Jose'""").show()

#DATAFRAME CODE

df.select(['cnum','cname','city','ranking','snum']).filter((df['city']=='San Jose') & (df['ranking']>200)).show()