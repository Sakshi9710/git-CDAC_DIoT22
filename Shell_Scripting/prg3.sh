echo "Enter Your Name : "
read Name
echo "Enter Your Prn : "
read prn;

if [[ "$Name" == "sakshi" ]];
then 
    echo "Your Name is : $Name"
if [[ "$prn" == 23 ]];
then
    echo " You are allowed to give Exam "
fi
else
    echo " You are not allowed to give Exam "
fi