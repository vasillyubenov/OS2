#!/bin/bash
if [ "$USER" != "root" ]; then
	total=$(ps aux | awk -v counter=0 'NR!=1 {counter+=$6} END{print counter}')
	for rss in $(ps aux | awk -F" " -v total=$total '{if($6>total/2 && NR!=1) print $2}' ); do
		kill $rss 2> /dev/null
	done
fi
