from pyspark.sql import SparkSession

spark = SparkSession.builder.appName('Basic').getOrCreate()

empDF = spark.read.csv('emp.csv',inferSchema=True,header=True)
deptDF = spark.read.csv('dept.csv',inferSchema=True,header=True)

empDF.join (deptDF, empDF.emp_dept_id  ==  deptDF.dept_id,"inner").show()

empDF.join (deptDF, empDF.emp_dept_id == deptDF.dept_id,"outer").show()

empDF.join (deptDF, empDF.emp_dept_id == deptDF.dept_id,"full").show()

empDF.join (deptDF, empDF.emp_dept_id == deptDF.dept_id,"fullouter").show()

empDF.join (deptDF, empDF.emp_dept_id == deptDF.dept_id,"left").show()

empDF.join (deptDF, empDF.emp_dept_id==deptDF.dept_id,"leftouter").show()

empDF.join (deptDF, empDF.emp_dept_id == deptDF.dept_id,"right").show()

empDF.join (deptDF, empDF.emp_dept_id == deptDF.dept_id,"rightouter").show()