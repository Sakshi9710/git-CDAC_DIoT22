i=50
while [ $i -gt 5 ]
do
    echo "value of i is $i"
    (( i = i-5 ))
if [ $i -eq 10 ]
then
break;
fi
done