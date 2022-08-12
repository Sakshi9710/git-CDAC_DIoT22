#5.find jobs and balance that have balance value higher than the average of blue-collar people

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

#print(bank_rdd)

dict_rdd = selectedBankField.groupByKey ().mapValues ( lambda x : sum (x) / len (x))

totalBlueCollar = selectedBankField.filter(lambda x : x[0]=='blue-collar')

onlyBalance= totalBlueCollar.map ( lambda x : int(x[1]))

balancelist = onlyBalance.collect()

totalBlueCollarPeople= sum(balancelist) / len(balancelist)

print(totalBlueCollarPeople)

highertotalBlueCollarPeople = selectedBankField.filter( lambda x : int(x[1])>totalBlueCollarPeople)

for element in highertotalBlueCollarPeople.collect():
    print("jobs : %s and Balance :%d " % (element[0] , element[1]))
