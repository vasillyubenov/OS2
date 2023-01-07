#!/bin/bash

file=$1
dir=$2

counter=1
oldIFS=$IFS
IFS=$'\n'
touch "$dir/dict.txt"	

for line in $(cat $file); do
	#getting the name
	name=""
	if [ $(echo $line | grep "(.*)" | wc -l) -ge 1 ]; then
		name=$(echo $line | cut -d" " -f1,2)
	else
		name=$(echo $line | cut -d":" -f1)
	fi
	
	if [ $(cat "$dir/dict.txt" | grep "$name;" | wc -l) -lt 1 ];  then
		touch "$dir/$counter.txt" 
		echo "$name; $counter" >> "$dir/dict.txt"
		echo $line >> "$dir/$counter.txt"
		counter=$((counter + 1))
	else
		num=$(cat "$dir/dict.txt" | grep "$name;" | cut -d";" -f2 | cut -c 2-)
		echo $line >> "$dir/$num.txt"
	fi
done
IFS=$oldIFS
