from pyspark.sql import SparkSession
spark = SparkSession.builder.appName('Basic').getOrCreate()
df=spark.read.csv('appl_stock.csv',inferSchema = True , header = True)

df.printSchema()
df.filter('Close<500').show()
# df.filter( (df['Close'] <500) & (df ['Open'] >200) ).select(['Open','Close']).show()

df.filter( (df['Close'] <500) & (df ['Open'] >200) ).select(['Open','Close']).show(100)