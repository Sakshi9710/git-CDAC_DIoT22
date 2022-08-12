read -p "Enter Number : " Number

if [[ Number -gt 0 ]]
then 
    echo " Number is positive "
elif [[ Number -lt 0 ]]
then 
    echo " Number is Negative "
else
    echo "Number is neither Positive nor Negative"
fi