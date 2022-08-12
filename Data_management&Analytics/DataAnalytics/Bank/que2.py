#Find the total number of married and unmarried couple
import sys
from pyspark import SparkContext

sc = SparkContext()

#count by key
print("**output By COUNT BY KEY **")
output = sc.textFile("bank.csv") \
        .map( lambda x: (x.split(',')[2],1) ) \
        .countByKey()

dict_rdd=output.items()

for key,value in dict_rdd:
    print(key,value)

#reduce by key
print("**output By REDUCE BY KEY **")
output = sc.textFile("bank.csv") \
        .map( lambda x: (x.split(',')[2],1) ) \
        .reduceByKey( lambda x, y:x+y )

print(output.collect())

#filter
print("**output By REDUCE BY KEY **")
output = sc.textFile("bank.csv") \
        .map( lambda x: (x.split(',')[0],1) ) \
        .filter(lambda x,y:x+y ) 

print(output)