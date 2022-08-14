even()
{
    if [[ $1%2 == 0 ]];
    then
        echo "$1 is even number"
    else    
        echo "$1 is not an even number"
    fi
}

read -p "Enter Number : " num
even $num