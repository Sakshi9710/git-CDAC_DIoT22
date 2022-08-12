import sys
from pyspark import SparkContext, SparkConf
sc = SparkContext("local","filter example")

rdd = sc.parallelize([1,2,3,4,5,6,7,8,9,12,1,2,3,4,5,7,5,4,"Hello","Hi","Welcome","hi"])

#map()
myOutput = rdd.distinct().collect()

print(myOutput)




