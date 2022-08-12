#find the average balance of blue-collar divorced people

from posixpath import split
import sys

from matplotlib.cbook import ls_mapper
from pyspark import SparkContext

sc = SparkContext()

bankData = sc.textFile("bank.csv") 

bank_lines = bankData.map(lambda l: l.split(","))

#only get job,martial status and balanced Field
selectedBankField = bank_lines.map(lambda x : (x[1],x[2],x[5]))

filteredData = selectedBankField.filter( lambda x : (x[0] =='blue-collar' and x[1] =='divorced'))

#only get the balance field - convert to integer
onlyBalance = filteredData.map(lambda f : int((f[2])))

#convert to a list
balanceList = onlyBalance.collect()

avgBalance = sum (balanceList) / len (balanceList)
        
print("Average Balance is : %d " % avgBalance)


