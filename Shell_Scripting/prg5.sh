read -p "Enter Number1 : " Number1
read -p "Enter Number2 : " Number2

# sum=`expr $Number1 + $Number2`
# sum=$(expr $Number1 + $Number2)
sum=$(($Number1 + $Number2))
echo "$Number1 + $Number2 = $sum"