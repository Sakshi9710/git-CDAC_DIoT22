read -p "Enter student name= " student_name
read -p "Enter Branch name= " branch_name
read -p "Enter Student Age = " age
read -p "Enter Salary = " salary
if [[ "$student_name" = "Nancy" ]];
then
if [[ "$branch_name" = "act" ]];
then
    echo "$student_name you are part of this organization $branch_name "
fi
else
    echo "You are not allowed to enter"
fi
if [ "$salary" -eq 1234 ];
then
if [ "$age" -eq 22 ];
then    
    echo "you are no more a student but employee"
fi
else
echo "you are still student work hard to became an employee"
fi