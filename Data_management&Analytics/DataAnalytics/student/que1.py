#calculate average year-wise marks (i.e for 2 semester for a year) for each student
# wxample - si1,year1,62.239999

from pickle import FALSE
from posixpath import split
import sys

from matplotlib.cbook import ls_mapper
from pyspark import SparkContext

sc = SparkContext()

studentData = sc.textFile("student.txt") 

student_lines = studentData.map(lambda l: l.split(","))

selectedstudentData = student_lines.map(lambda x : (x[0],x[1],(float(x[2])+float(x[3]))/2))

for i in selectedstudentData.sortByKey(FALSE).collect():
    print(i)





