#!/bin/bash

maxvalue=-1
negCount=0
posCount=0
input=""
while read line; do
	if [ $(echo $line | wc -c) -eq 1 ]; then
		break
	elif [ $(echo $line | egrep "^[-]{0,1}[0-9]+$" | wc -l) -eq 1 ];  then
		input+=" $line"
	fi
done

IFS=$'\n'
for num in $(echo $input | tr " " "\n"); do
	unset IFS
	abs=$num
	if [ $num -lt 0 ]; then
		abs=$((-abs))	
	fi
	
	if [ $abs -ge $maxvalue ]; then
		maxvalue=$abs
		if [ $abs -eq $maxvalue ]; then
			if [ $num -gt 0 ]; then
				posCount=1
			else
				negCount=1
			fi
		else
			posCount=0
			negCount=0
		
		fi
	fi
done

if [ $negCount -eq 1 ]; then
	echo "-$maxvalue"
fi

if [ $posCount -eq 1 ]; then
	echo $maxvalue
fi
