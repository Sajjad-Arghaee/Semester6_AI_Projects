#!/bin/bash
file="tasks.txt"

if [ ! -e "$file" ] ; then
    touch "$file"
fi

if [ $1 == "add" ];then
	if [ -z ${2+x} ]; then
		echo "[Error] This command needs an argument" >&2;
		exit 1;
	fi
	prefix="add"
	line=${@#"$prefix"}
	count=$(wc -l < "tasks.txt")
	count=$((count+1))
	if [[ ${line,,} == *"(very important)" ]]; then
	  	echo "Added task" $count "with priority H"
	  	echo "H" $line >> tasks.txt

	elif [[ ${line,,} == *"(important)"* ]]; then
	  	echo "Added task" $count "with priority M"
	  	echo "M" $line >> tasks.txt
	else
		echo "Added task" "$count" "with priority L"
		echo "L" $line >> tasks.txt
	fi
	

elif [ $1 == "list" ];then
	line_number=0
	count=$(cat "tasks.txt")
	if [ ! -e $count ];then
		echo "No tasks found..." >&2
	else
		while IFS= read -r line; do
			if [[ $line == "L"* ]]; then
				line_number=$((line_number+1))
			  	echo $line_number "*    " ${line:1}
			elif [[ $line == "M"* ]]; then
				line_number=$((line_number+1))
			  	echo $line_number "***  " ${line:1}
			elif [[ $line == "H"* ]]; then
				line_number=$((line_number+1))
				echo $line_number "*****" ${line:1}
			fi
			
			
		    
		done < tasks.txt
		if [ $line_number == "0" ];then
			echo "No tasks found..." >&2
		fi
	
	fi
	

elif [ $1 == "done" ];then
	if [ -z ${2+x} ]; then
		echo "[Error] This command needs an argument" >&2;
		exit 1;
	fi
	line=$(sed $2'!d' tasks.txt)
	echo "Completed task $2:"${line:1}
	sed -i "${2}d" tasks.txt
	
else
	echo "[Error] Invalid command" >&2
	exit 1;
	
fi

