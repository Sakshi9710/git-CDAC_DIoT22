import sys
from pyspark import SparkContext, SparkConf
sc = SparkContext("local","map and flatMap example")

rdd = sc.parallelize([
            ("jan",2019,86000,56),
            ("jan",2020,71000,30),
            ("jan",2021,90000,24),

            ("feb",2019,99000,40),
            ("feb",2020,83000,36),
            ("feb",2021,69000,53),

            ("mar",2019,80000,25),
            ("mar",2020,91000,50)
            ])

#map()
myOutput = rdd.map(lambda x: (x[0],x[1],x[2],x[3]*100))
myDisplay = myOutput.collect()
print(myDisplay)

#flatMap()
myOutput = rdd.flatMap(lambda x: (x[0],x[1],x[2],x[3]*100))
myDisplay = myOutput.collect()
print(myDisplay)

