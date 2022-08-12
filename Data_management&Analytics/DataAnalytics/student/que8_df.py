#list of student who have higher average grade in the second year than the first year grade


from pyspark.sql import SparkSession
from pyspark.sql.types import StructField,StringType,StructType, FloatType, IntegerType
from pyspark.sql.functions import format_number , col

spark = SparkSession.builder.appName('Basic').getOrCreate()

dataSchema = [StructField  ('student_id',StringType(),True),
                StructField  ('year',StringType(),True),
                StructField  ('sem_1',FloatType(),True),
                StructField  ('sem_2',FloatType(),True)
                ]

final_struct = StructType( fields=dataSchema )

# studentDF = spark.read.text('student.txt')
df = spark.read.csv('student.txt',header=False, schema= final_struct)

firstFilteredData = df.filter(df['year']=='year1')

firstResult_df = firstFilteredData.select('student_id','year',format_number(((df['sem_1']+df['sem_2'])/2),2).alias("Sem1 Avg Marks"))

#firstResult_df.show()

secondFilteredData = df.filter(df['year']=='year2')

secondResult_df = secondFilteredData.select('student_id','year',format_number(((df['sem_1']+df['sem_2'])/2),2).alias("Sem2 Avg Marks"))

#secondResult_df.show()

final_df = firstResult_df.join (secondResult_df, firstResult_df.student_id  ==  secondResult_df.student_id,"inner")

final_df.filter(final_df["Sem2 Avg Marks"]>final_df["Sem1 Avg Marks"]).show()