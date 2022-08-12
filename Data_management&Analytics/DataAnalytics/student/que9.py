from posixpath import split
import sys

from matplotlib.cbook import ls_mapper
from pyspark import SparkContext

sc = SparkContext()

studentData = sc.textFile("student.txt") 

student_lines = studentData.map(lambda l: l.split(","))