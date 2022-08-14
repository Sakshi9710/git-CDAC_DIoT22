function division
{
    return $(($1/$2))
}

read -p "Enter the first number : " num1
read -p "Enter the second number : " num2
division $num1 $num2
echo $?