#!/bin/bash
min=$1
max=$2

mkdir a b c 2> /dev/null
for file in $(find . -maxdepth 1 -type f); do
	size=$(cat $file | wc -l)
	if [ $size -lt $min ]; then
		mv $file "a"
	elif [ $size -gt $min ] && [ $size -gt $max ]; then
		mv $file "b"
	else
		mv $file "c"
	fi
done
