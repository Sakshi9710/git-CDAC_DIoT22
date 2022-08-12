import sys
from pyspark import SparkContext, SparkConf
sc = SparkContext("local","PairRdd example")

marks = ([("Rahul",88),("Swati",92),("Shreya",83),("Abhay",93),("Rohan",78)])

output = sc.parallelize(marks).collect()

print(output)