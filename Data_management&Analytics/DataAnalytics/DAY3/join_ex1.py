import sys
from pyspark import SparkContext, SparkConf
sc = SparkContext("local","Pair Rdd example")

marks_rdd = sc.parallelize([("Rahul",25),("Swati",26),("Shreya",22),("Abhay",26),
                ("Rohan",22),("Rahul",23),("Swati",19),("Shreya",28),("Abhay",29),("Rohan",22)])

mobile_rdd = sc.parallelize([("Rahul",'987654123'),("Swati",'8875461238'),("Shreya",'7756891433'),("Abhay",'78955652535'),
                ("Rohan",'3634645487')])

final_rdd = marks_rdd.join(mobile_rdd)

for key,value in final_rdd.collect():
    print(key,list(value))