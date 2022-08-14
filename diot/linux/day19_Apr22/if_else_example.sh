read -p "Enter the name= " name
read -p "Enter the prn= " prn
if [[ "$name" = "Nancy" ]];
then
    echo "Your Name is = $name "
if [ "$prn" -eq 1234 ];
then
    echo "access to give exam"
fi
else 
    echo "not matched you are not allowed"
fi