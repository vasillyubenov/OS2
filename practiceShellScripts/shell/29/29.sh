#!/bin/bash

if [ $USER != "root" ]; then
	total=$(ps -e -o user:20,uid,pid,rss | awk -v counter=0 '{counter+=$4} END{print counter}' user=$user)
	threshold=$((total/2))

	for user in $(ps -e -o user:20,uid,pid,rss | awk '{if($1!="root" && NR!=1) print $1}' | sort | uniq); do
		user_home_dir=$(cat "/etc/passwd" | awk -v user=$user -F":" '$1==user{print $6}')
		#echo $user_home_dir
		if [[ ! -d  $user_home_dir ]] || [[ ! -r $user_home_dir ]] || [[ ! -O $user ]]; then
			#get the the name of the user if his procceses are larger than 1/2 max rss
			fat_user=""
			fat_user=$(ps -e -o user:20,uid,pid,rss | awk -v br=0 '{if($1==user) br+=$4} END{if(br>max) print user}' user=$user max=$threshold)
			#echo $fat_user
			if [ $(echo $fat_user | grep "[0-9A-Za-z]" | wc -l) -ge 1 ]; then
				procs_to_kill=$(ps -e -o user:20,uid,pid,rss | awk -v current_user=$fat_user '$1==current_user {procs=procs" "$3} END{print procs}' procs="")
				echo $procs_to_kill
				#did not want to kill all my proccesses on the local machine feel free to uncomment underline
				#kill $procs_to_kill
			fi
			
		fi
	done
fi
