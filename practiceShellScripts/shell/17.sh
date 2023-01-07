#!/bin/bash

if [ $USER = "vasetokaiba" ]; then
	br=0;
	for homedir in $(cat /etc/passwd | cut -d":" -f6); do 
		if [ $(echo $homedir | grep "^/home" | wc -l) -lt 1 ]; then
			cat /etc/passwd | awk -v counter=$br 'FNR==counter {print $0}'
		fi
		br=$((br + 1))
	done 
fi
