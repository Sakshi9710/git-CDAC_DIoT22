sum() {
    let result=$1+$2
    res=$(($1+$2))
    echo $res
    echo $result
}

sum "10" "20"

function quote
{
    echo "Hard work is key to sucess"
}
quote