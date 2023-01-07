#!/bin/bash

file1=$1
file2=$2

singer1name=$(echo $file1 | cut -d"." -f1)
singer2name=$(echo $file2 | cut -d"." -f1)
size1=$(cat $file1 | grep $singer1name | wc -l)
size2=$(cat $file2 | grep $singer2name | wc -l)

if [ $size1 -lt $size2 ]; then
	cat $file2 | cut -d" " -f4- | sort > "${singer2name}.songs"
else
	cat $file1 | cut -d" " -f4- | sort > "${singer1name}.songs"
fi
