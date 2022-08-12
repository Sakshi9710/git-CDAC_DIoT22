#calculate average year-wise marks (i.e for 2 semester for a year) for each student for
# example - si1,year1,62.239999

from pyspark.sql import SparkSession
from pyspark.sql.types import StructField,StringType,StructType, FloatType, IntegerType
from pyspark.sql.functions import format_number

spark = SparkSession.builder.appName('Basic').getOrCreate()

dataSchema = [StructField  ('student_id',StringType(),True),
                StructField  ('year',StringType(),True),
                StructField  ('sem_1',FloatType(),True),
                StructField  ('sem_2',FloatType(),True)
                ]

final_struct = StructType( fields=dataSchema )

# studentDF = spark.read.text('student.txt')
df = spark.read.csv('student.txt',header=False, schema= final_struct)

result_df = df.select('student_id','year',format_number(((df['sem_1']+df['sem_2'])/2),2).alias("Avg Marks"))

result_df.filter(df['year']=='year2').show()