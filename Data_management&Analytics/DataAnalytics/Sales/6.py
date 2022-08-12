from pyspark.sql import SparkSession

spark = SparkSession.builder.appName('Missing').getOrCreate()
df=spark.read.csv('ContainNullValues.csv',inferSchema = True , header = True)

df.show()

#Drop row that have any null value
df.na.drop().show()

#A row must have atleat two non null columns to appear in the output
df.na.drop(thresh = 2 ).show()

#drop rows that have any null value columns
df.na.drop(how = 'any' ).show()

#drop rows that have all null value columns
df.na.drop(how = 'all' ).show()

#Drop Rows that have a null value in the Sales Columns
df.na.drop(subset=['Sales'] ).show()

#Fill null values with our own value
df.na.fill('DUMMY INSERT').show()

#Fill null values with zeroes for numeric columns
df.na.fill(0).show()

#Fill null values only for names columns with own values
df.na.fill('No name',subset=['Name']).show()