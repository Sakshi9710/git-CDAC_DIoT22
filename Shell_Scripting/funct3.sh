greatest()
{
    if [[ $1 -gt $2 ] && [ $1 -gt $3 ]];
    then
        echo "$1 is greatest"
    elif [[ $2 -gt $3 ]]
     then
        echo "$2 is greatest"
    else
        echo "$3 is greatest"
}

echo "Enter 3 Numbers:-"
read num1 
read num2 
read num3

greatest $num1 $num2 $num3