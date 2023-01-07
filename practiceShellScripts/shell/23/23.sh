#!/bin/bash
minTime=0
current=0
newest_file=""
# do a loop for every dir have to only change /home = current dir (from loop)
for file in  $(find /home -maxdepth 2 -type f); do
	current_file_epoch=$(stat -c"%Y" $file)
	if [ $current -eq 0 ] || [ $minTime -lt $current_file_epoch ]; then
		minTime=$current_file_epoch
		newest_file=$file
		current=$((current + 1))
	fi
done

echo "$newest_file $minTime"
