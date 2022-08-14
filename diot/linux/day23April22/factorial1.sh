factorial()
{
    fact=1
    for((i=1;i<=num,i++))
    do 
        fact=$((fact*i)) 
        echo "Factorial of num number is : $fact"
    done
    
}

read -p "Enter Number : " num
factorial $num