#!/bin/bash
dest=$1
counter=0
if [ -e $dest ]; then
	if [ $# -eq 2 ]; then
		for link in $(find $dest -type l); do
			if [ $(file $link | grep ": broken symbolic link" | wc -l) -eq 1 ]; then
				counter=$((counter + 1))
			else
				stat -c"%N" $link >> $2
			fi
		done
		echo "broken links counted: $counter" >> $2;
	else
		for link in $(find $dest -type l); do
			if [ $(file $link | grep ": broken symbolic link" | wc -l) -eq 1 ]; then
				counter=$((counter + 1))
			else
				stat -c"%N" $link
			fi
		done
		echo "broken links counted: $counter";
	fi
fi
