#!/bin/bash

index_array = (1,2,3,4,5)
echo ${index_array[0]}

for i in ${index_array[@]}
do 
    echo $i #print all the value of array
done 

echo "Length of the array is : ${#index_array[@]}" #length of the array

name[0] ="AAA"
name[1] ="BBB"
name[2] ="CCC"
name[3] ="DDD"
name[4] ="EEE"

echo "First Index Value : ${name[0]}"
echo "All members of Array : ${name[*]}"
echo "All members : ${name[@]}"
