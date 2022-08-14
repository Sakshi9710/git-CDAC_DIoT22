read -p "any command : " file

while IFS= read -r line; do
    echo $line
done < "file"