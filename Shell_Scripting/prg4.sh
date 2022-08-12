echo "Enter Your Name : "
read Name
echo "Enter Your Branch Name : "
read branch_name;
echo "Enter Your Age  : "
read Age
echo "Enter Your Salary : "
read salary

if [[ "$Name" == "sakshi" && "$branch_name" == "cdac_act" ]];
then 
    echo "$Name is the part of the Organization $cdac_act"
else
    echo "You are not a part of this Organization"
fi
if [[ "$age" == 23 && "$salary" -gt 10000 ]];
then
    echo " You are a Employee "
else
    echo " You are a Student Not a employee "
fi