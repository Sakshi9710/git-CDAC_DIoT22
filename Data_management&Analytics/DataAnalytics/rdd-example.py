import sys
from pyspark import SparkContext, SparkConf
sc = SparkContext("local","PySpark RDD example")

myRDD = sc.parallelize([('Big Data',80),('Python',80),('ML',56),('Java',67),('Web Analytics',78),('Good Programming Pratices',67),('Software Design',77)])

myRDD.take(7)
myRDD.saveAsTextFile('myRDD/')
