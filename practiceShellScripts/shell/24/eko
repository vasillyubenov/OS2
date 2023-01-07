#!/bin/bash

dir=$1

if [ -d $dir ]; then
	if [ "$#" -eq 1 ]; then
		find $dir -xtype l 
	else 
		for file in $(find $dir -maxdepth 5 -type f); do
			if [ -e $file ]; then
				if [ $(stat -c "%h" $file) -ge $2 ]; then
					echo $file
				fi
			fi
		done
	fi

fi
