#!/bin/bash

if [ "$#" -eq 0 ]
then
    echo "There is no input data."
    exit 1
fi

sum=0
count=0

for num in "$@"
do
    sum=$((sum + num))
    count=$((count + 1))
done

average=$(echo "scale=2; $sum / $count" | bc)

echo "Count: $count"
echo "Average: $average"
