#!/bin/bash

src=$1
dest=$2
str=$3

for dir in $(find $src -type d); do
	dir_to_make=$(echo $dir | tr -s ".")
	if [ $dir_to_make != "." ]; then
		mkdir $dir_to_make
		for file in $(find $dir -maxdepth 1 -type f); do
			if [ $(basename $file | grep $str | wc -l) -ge 1 ]; then
				cp $file $dir_to_make
			fi
		done
	fi
done 
