function subtract
{
  return expr $1-$2
  
}

read -p "Enter the first number : " num1
read -p "Enter the second number : " num2
subtract $num1 $num2
echo $?
echo "$num1-$num2 = $subres"