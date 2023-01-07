#!/bin/bash

line_num=10
start_arg=1
if [ $1 = "-n" ]; then
	line_num=$2
	start_arg=3
fi

br=1
#echo $start_arg
for i in $@; do
	if [ $br -lt $start_arg ]; then
		br=$((br + 1))
		continue
	fi
	id=$(echo $i | cut -d"." -f1)
	IFS=$'\n'
	
	output=""
	for data in $(cat $i | tail -n $line_num ); do
		first=$(echo $data | awk -v var=$id -F" " '{printf "%s %s %s", $1, $2, var}')
		rest=$(echo $data | cut -d" " -f3-)
		IFS=$'\n'
		if [ -z $(echo $output)  ]; then
			IFS=$"\n"
			output=$(echo -e "$first $rest")		
		else	
			IFS="\n"
			output=$(echo -e "$output \n$first $rest")			
		fi

	done
	
	echo $output | sort 
done

unset IFS
