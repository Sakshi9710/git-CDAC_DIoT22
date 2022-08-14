read -p "Enter Number = " number

if [ $number -gt 0 ];
then   
    echo "Number is Positive"
elif [ $number -lt 0 ]
then
    echo "Number is Negative"
else
    echo "Number is neither Negative nor Positive"
fi