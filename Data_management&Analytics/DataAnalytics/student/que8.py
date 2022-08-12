#list of student who have higher average grade in the second year than the first year grade

from posixpath import split
import sys

from matplotlib.cbook import ls_mapper
from pyspark import SparkContext

sc = SparkContext()

studentData = sc.textFile("student.txt") 

student_lines = studentData.map(lambda l: l.split(","))

firstYearMarks = student_lines.filter(lambda x : x[1]=='year1')

firstYearMarksMean = firstYearMarks.map(lambda x : [x[0],x[1],(float(x[2])+float(x[3]))/2])

firstYearMarksMeanList = firstYearMarksMean.collect()

secondYearMarks = student_lines.filter(lambda x : x[1]=='year1')

secondYearMarksMean = secondYearMarks.map(lambda x : [x[0],x[1],(float(x[2])+float(x[3]))/2])

secondYearMarksMeanList = secondYearMarksMean.collect()

i=0

print("List of students whose second year aggregrate is higher than that of the first year...")

for firstlistElement in firstYearMarksMeanList:
    secondListElement = secondYearMarksMeanList[i]

    if(secondListElement [2] > firstlistElement[2] ) :
        print("Student : %s,Second Year Aggregrate : %f , First Year Aggregrate : %f" %(firstlistElement[0],secondListElement[2],firstlistElement[2]))
        i +=1