read -p "Enter the destination of the file to be copied : " path 
read -p "Enter the name of file : " file_name
mv $file_name $path
echo "Copied Successfully"