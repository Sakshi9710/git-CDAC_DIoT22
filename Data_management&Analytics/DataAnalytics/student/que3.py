#show sorted (highest to lowest) average grades in the second year.

from pickle import FALSE
from posixpath import split
import sys

from matplotlib.cbook import ls_mapper
from pyspark import SparkContext

sc = SparkContext()

studentData = sc.textFile("student.txt")

student_lines = studentData.map(lambda l: l.split(","))

selectedstudentData = student_lines.map(lambda x : (x[0],x[1],(float(x[2])+float(x[3]))/2))

studentMarks=selectedstudentData.filter(lambda x : 'year2' in x )

sortedMarks =  studentMarks.sortBy(lambda x : -x[2])

print(sortedMarks.collect())

