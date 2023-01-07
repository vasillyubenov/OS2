#!/bin/bash

dir=$1
mkdir "extracted" 2> /dev/null

if [ -d $dir ]; then
	IFS=$'\n'
	for file in $(find $dir -type f | egrep "^.+_.+-[0-9]+.tgz$"); do
		unset IFS
		
		if [ $(tar -tf $file | grep "meow.txt$" | wc -l) -ge 1 ]; then
			name=$(basename $file | cut -d "_" -f1);
			timestamp=$(basename $file | cut -d"-" -f2 | cut -d"." -f1);
			mv $file "/extracted/$name_$timestamp.txt"	
		fi
	done
fi
