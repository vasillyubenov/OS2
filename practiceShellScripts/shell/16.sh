#!/bin/bash

dir=$1

if [ -d $dir ]; then
	for file in $(find $dir -type l); do
		if [ ! -e "$F" ] ; then
    			echo $file
		fi
	done 
fi
