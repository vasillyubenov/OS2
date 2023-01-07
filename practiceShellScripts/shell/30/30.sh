#!/bin/bash

#LOGDIR/protocol/accaunt/friend/
logdir=$1
counter=0

best_friend_name=""
best_friend_msgs=0

for friend in $(find $logdir -mindepth 3 -maxdepth 3 -type d | xargs -I {} basename {} | sort | uniq); do
	current_friend_msgs=0
	for fr in $(find $logdir -maxdepth 3 -name $friend); do
		current_msgs=$(find $fr -maxdepth 1 -type f | egrep "[0-9]{4}-[0-9]{2}-[0-9]{2}-[0-9]{2}-[0-9]{2}-[0-9]{2}.txt$" | xargs -I {} cat {} | wc -l)
		#echo "$friend $current_msgs"
		current_friend_msgs=$((current_friend_msgs + current_msgs))	
	done
	
	if [ $best_friend_msgs -le $current_friend_msgs ]; then
		best_friend_msgs=$current_friend_msgs
		best_friend_name=$friend
	fi
done

echo "$best_friend_name $best_friend_msgs"
