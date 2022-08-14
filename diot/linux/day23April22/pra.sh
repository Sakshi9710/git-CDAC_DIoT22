function arthmetic
{
    let res=($1+$2)*$3
    echo $res
}

read -p "Enter Number1 : " num1
read -p "Enter Number2 : " num2
read -p "Enter Number3 : " num3
arthmetic $num1 $num2 $num3