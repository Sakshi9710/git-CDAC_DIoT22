#!/bin/bash
factorial()
{
    fact=1
    for i in {1..5}
    do 
        fact=$((fact*i)) 
    done
    echo "Factorial of num number is : $fact"
}

#read -p "Enter Number : " num
factorial 