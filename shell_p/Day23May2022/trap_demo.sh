#!/bin/bash
trap "echo once signal is sent I will be terminated" EXIT
i=1
while true
    do
        echo "the value of i is $i"
        ((i++))
    done