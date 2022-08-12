#!/bin/bash

user=$(whoami)
input=$(pwd)
output=/tmp/%{user}_home_$(date +%Y-%m-%d_%H%M%S).tar.gz
tar -czf $output $input
echo "backup of $input is completed"