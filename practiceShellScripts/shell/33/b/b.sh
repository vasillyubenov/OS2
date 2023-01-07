#!/bin/bash

maxsum=-1
input=""
minnum=0
counter=0
while read line; do
	if [ $(echo $line | wc -c) -eq 1 ]; then
		break
	elif [ $(echo $line | egrep "^[-]{0,1}[0-9]+$" | wc -l) -eq 1 ];  then
		linesum=0
		input+=" $line"
		allnums=$(echo $line | wc -c)
		start=1
		if [ $line -lt 0 ]; then
			start=2
		fi
		
		for i in $(seq $start $allnums); do
			currentNum=$(echo $line | cut -c $i)
			
			if [ $(echo $currentNum | egrep "^[0-9]+$" | wc -l) -eq 1 ]; then
				linesum=$((linesum+currentNum))
			fi
		done
		
		if [ $linesum -gt $maxsum ]; then
			maxsum=$linesum
		fi
	fi
done

for num in $(echo $input); do
	linesum=0
	allnums=$(echo $num | wc -c)
	start=1
	if [ $num -lt 0 ]; then
		start=2
	fi
	
	for i in $(seq $start $allnums); do
		currentNum=$(echo $num | cut -c $i)
		
		if [ $(echo $currentNum | egrep "^[0-9]+$" | wc -l) -eq 1 ]; then
			linesum=$((linesum+currentNum))
		fi
	done
	
	if [ $linesum -eq $maxsum ] && [ $num -lt $minnum ] || [ $counter -eq 0 ]; then
		counter=1
		minnum=$num
	fi
done

echo $minnum
