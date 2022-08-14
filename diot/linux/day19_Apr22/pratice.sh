read -p "Enter the command= " command
if [[ "$command" = "mkdir" ]];
then
    echo "Entered command is = $command "
else 
    echo "Entered command not found"
fi