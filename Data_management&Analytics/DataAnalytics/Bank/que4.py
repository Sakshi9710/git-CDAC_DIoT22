#4.Find the total and Average Balance for each type of job

from posixpath import split
import sys

from matplotlib.cbook import ls_mapper
from pyspark import SparkContext

sc = SparkContext()

bankData = sc.textFile("bank.csv") 

bank_lines = bankData.map(lambda l: l.split(","))

#only get job,martial status and balanced Field
selectedBankField = bank_lines.map(lambda x : (x[1],int(x[5])))

#print(selectedBankField.collect())

bank_rdd = selectedBankField.reduceByKey(lambda x,y : (int(x)+int(y))).collect()

print(bank_rdd)

# dict_rdd = selectedBankField.countByKey().items()

# for key,value in dict_rdd:
#     print(key,value)

# avgBalance = sum (bank_rdd) / len (dict_rdd)
        
        
# print("Average Balance is : %d " % avgBalance)

dict_rdd = selectedBankField.groupByKey ().mapValues ( lambda x : sum (x) / len (x))

for elements in dict_rdd.collect():
    print(elements)
