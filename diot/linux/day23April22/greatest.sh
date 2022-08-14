greatest()
{
    if [ $1 -gt $2 ] && [ $1 -gt $2 ];
        then
            echo "num1 $1 is Greater"
    elif [ $2 -gt $3 ];
        then
            echo "num2 $2 is Greater"
    else
       echo "num3 $3 is Greater"
    fi
    
    
}

read -p "Enter the first number : " num1
read -p "Enter the second number : " num2
read -p "Enter the Third number : " num3

greatest $num1 $num2 $num3