for i in 1 2 3 4 5 
do 
    echo "Loop runs $i times"
done

for i in {1..4}
do 
    echo "Loop runs $i times"
done

for i in {0..10..2}
do 
    echo "Loop runs $i times"
done

read -p "Enter your string to calculate Lenght : " str_var
echo "${#str_var}"