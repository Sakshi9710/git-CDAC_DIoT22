import sys
from pyspark import SparkContext, SparkConf

if __name__=="__main__" :

    #create Spark context with Spark Configuration
    conf = SparkConf().setAppName("Read Text to RDD - Python")
    sc = SparkContext(conf=conf)

    #read input Text file to RDD
    numbers=sc.parallelize([1,2,3,4,5,6,7,8,9,10])

    #filtered data
    filteredData = numbers.filter(lambda x : x!=5).collect()

    #Now Distinct Data
    for num in filteredData:
        print("%i"%(num))