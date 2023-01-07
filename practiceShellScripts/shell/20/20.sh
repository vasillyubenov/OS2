#!/bin/bash

file=$1
counter=1
if [ -e $file ]; then
	cat $file | cut -d" " -f3- | nl -s"." | tr -s " " | sort -t"\"" -k2,2
fi 
