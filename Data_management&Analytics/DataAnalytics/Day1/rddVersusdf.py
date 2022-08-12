#calculate average age and print
#the corresponding DataFrame example is rddVersusudf-2.py

from pyspark import SparkContext

sc = SparkContext()

dataRDD = sc.parallelize([('Sachin',49),('Rahul',51),('MSD',40),('Sachin',67),('Rahul',41),('MSD',30),('sunil',63)])

agesRDD= (dataRDD
        .map(lambda x : (x[0],(x[1],1)))
        .reduceByKey (lambda x , y : (x[0]+y[0],x[1]+y[1]))
         .map(lambda x : (x[0],x[1][0]/x[1][1]))
        )
print (agesRDD.collect())