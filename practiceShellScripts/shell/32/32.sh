#!/bin/bash
a=$1
b=$2

oldIFS=$IFS
IFS=$'\n'
counter=0
current_file=""
for line in $(cat $a); do
	ind=$(echo $line | cut -d"," -f1)
	rest=$(echo $line | cut -d"," -f2-)
	
	IFS='\n'
	file=$(cat $a | awk -F"," '{if(ind<$1 && $2","$3","$4==rest) $1=ind} {print $1","$2","$3","$4}' rest=$rest ind=$ind)
	echo $file > $a
done

unset IFS;

for line in $(cat $a); do
	#in case we have don't duplicates
	if [ $(cat $a | grep $line | wc -l) -eq 1 ]; then
		echo "$line" >> $b
	fi
done
IFS="\n"
unique=$(cat $a | sort | uniq)
echo $unique > $a
