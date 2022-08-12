for file in *.html
do
    echo $file
    echo "{$file%.html}.txt"
    mv "$file" "${file%.html}.txt"
done