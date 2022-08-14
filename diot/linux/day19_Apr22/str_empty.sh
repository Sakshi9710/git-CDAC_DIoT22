#check if string is empty
str="Sakshi"
str_1=''

if [[ -z $str1 ]]
then 
    echo "string is empty"
else    
    echo "string is not empty"
fi

if [[ -n $str ]]
then 
    echo "string is not empty"
else    
    echo "string is empty"
fi