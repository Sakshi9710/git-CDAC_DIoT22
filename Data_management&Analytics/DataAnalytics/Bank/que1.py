#Count number of user of every age
import sys
from pyspark import SparkContext

sc = SparkContext()

#reduce by key
print("**output By REDUCE BY KEY **")
output = sc.textFile("bank.csv") \
        .map( lambda x: (x.split(',')[0],1) ) \
        .reduceByKey( lambda x, y:x+y )

print(output.collect())

#using count by key

print("**output By count BY KEY **")
output = sc.textFile("bank.csv") \
        .map( lambda x: (x.split(',')[0],1) ) \
        .countByKey()

print(output.items())

dict_items = output.items()

print("**Each item in the Dictonary**")

for key,value in dict_items:
    print("Age:%s , Number of customers : %s"% (key,value) )

