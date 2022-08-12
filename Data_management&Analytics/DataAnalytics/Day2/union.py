import sys
from pyspark import SparkContext, SparkConf
sc = SparkContext("local","filter example")

rdd = sc.parallelize([1,2,3,4,5,6,7,8,9,12])
other = sc.parallelize([3,14,19,4,5])
#UNIONs
myOutput = rdd.union(other).collect()

print(myOutput)

#INTERSECTION
myOutput = rdd.intersection(other).collect()

print(myOutput)


