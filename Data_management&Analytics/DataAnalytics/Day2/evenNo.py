import sys
from pyspark import SparkContext, SparkConf
sc = SparkContext("local","map and flatMap example")

numbers = range(1,10)
myOutput = list(filter(lambda x : (x%2==0 ) , numbers))

print(myOutput)

rdd = sc.parallelize([1,2,3,4,5,6,7,8,9,10])

#map()
myOutput = rdd.filter(lambda x : x%2==0 ).collect()

print(myOutput)




