#!/bin/bash
dir=$1
str=$2

if [ -e $dir ]; then
	top_file=$(find $dir -maxdepth 1 -type f | awk -F"-" '$NF==arch {print}' arch=$str | sort -nr -t"-" -k2,2 | head -1)
	basename $top_file
fi 
