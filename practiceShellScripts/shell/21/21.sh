#!/bin/bash

filename=$1
str1=$2
str2=$3
counter=1
oldIFS="$IFS"
IFS="\n"

if [ -e $filename ]; then
	first=$(awk -F"=" -v str=$str1 '{if($1==str) print}' $filename)
	second=$(awk -F"=" -v str=$str2 '{if($1==str) print}' $filename)
	IFS=" "
	newline=$(echo "$(echo $second | cut -d"=" -f1)=")

	for trap in $(echo $second | cut -d"=" -f 2); do
		if [ $(echo $first | cut -d"=" -f 2 | grep $trap | wc -l) -eq 0 ]; then
			if [ $counter -eq 1 ]; then
				newline="$newline$trap"	
			else
				newline="$newline $trap"	
			fi
			counter=$((counter + 1))
		fi
	done
	IFS="\n"
	awk -F"=" '$1==str {$0=newline; print $0} $1!=str {print}' str=$str2 newline=$newline $filename
fi

IFS="$oldIFS"
