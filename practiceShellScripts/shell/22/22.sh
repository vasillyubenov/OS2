#!/bin/bash

username=$1

if [ $(echo "$USER") != "root" ]; then
	userprocs=$(ps -e -o user:20,pid,%cpu,%mem,vsz,rss,tty,stat,time,command | awk -v user=$username 'user==$1 {print $1}' | wc -l)

	hours=0
	min=0
	seconds=0

	current_hours=0
	current_mins=0
	current_seconds=0

	for user in $(ps -e -o user:20,pid,%cpu,%mem,vsz,rss,tty,stat,time,command | awk '{print $9}' | sort | uniq); do
		#a)
		#if [ $(ps -e -o user:20,pid,%cpu,%mem,vsz,rss,tty,stat,time,command | awk -v user=$user 'user==$1 {print $1}' | wc -l) -gt $userprocs ]; then
		#	echo $user	
		#fi
		#b)
		current_seconds=$(echo $user | cut -d":" -f3)
		
		while [ $(echo $current_seconds | grep "^0" | wc -l) -gt 0 ]; do
			current_seconds=$(echo $current_seconds | cut -c 2-)
		done
		
		seconds=$((seconds + current_seconds))
		
		current_hours=$(echo $user | cut -d":" -f1)
		
		while [ $(echo $current_hours | grep "^0" | wc -l) -gt 0 ]; do
			current_hours=$(echo $current_hours | cut -c 2-)
		done
		
		hours=$((hours + current_hours))
		
		current_mins=$(echo $user | cut -d":" -f2)
		
		while [ $(echo $current_mins | grep "^0" | wc -l) -gt 0 ]; do
			current_mins=$(echo $current_mins | cut -c 2-)
		done
		
		min=$((min + current_mins))			
	done
	
	min=$((min + seconds/60))
	hours=$((hours + min/60))

	min=$((min/60))
	seconds=$((seconds/60))

	normalIFS=$IFS
	IFS="\n"
	allTime=$((seconds + mins*60 + hours*3600))
	for proc in $(ps -e -o pid,time); do
		currentProcTime=$(echo $proc | cut -f2)
		
		current_seconds=$(echo $currentProc | cut -d":" -f1)
		
		while [ $(echo $current_seconds | grep "^0" | wc -l) -gt 0 ]; do
			current_seconds=$(echo $current_seconds | cut -c 2-)
		done
		
		current_mins=$(echo $currentProc | cut -d":" -f2)
		
		while [ $(echo $current_mins | grep "^0" | wc -l) -gt 0 ]; do
			current_mins=$(echo $current_mins | cut -c 2-)
		done
		
		current_hours=$(echo $currentProc | cut -d":" -f2)
		
		while [ $(echo $current_hours | grep "^0" | wc -l) -gt 0 ]; do
			current_hours=$(echo $current_hours | cut -c 2-)
		done
		
		currentPid=$(echo $proc | cut -f1)
		
		currentProcTime=$((current_seconds + current_mins*60 + current_hours*3600))
		
		if [ $currentProcTime -ge $((allTime/2)) ]; then
			echo $currentPid
		fi
		#printf "%s\n" $proc
	done
	IFS=$normalIFS
	#printf "%2.2d:%2.2d:%2.2d\n" $hours $min
fi
