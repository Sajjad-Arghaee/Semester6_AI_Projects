#!/bin/bash

# part one:
mkdir dir1
touch dir1/file1.txt
chmod 727 dir1/file1.txt
sudo groupadd group1
for i in {1..25}; do sudo useradd -m -G group1 new_users$i; done
sudo chgrp group1 dir1/file1.txt
chmod g+r dir1/file1.txt


# part two
mkdir dir2
touch dir2/file2.sh
chmod 767 dir2/file2.sh
sudo groupadd group2
for i in {1..25}; do sudo useradd -m -G group2 users$i; done
sudo chgrp group2 dir2/file2.sh
chmod g+x dir2/file2.sh


# part three
touch pass_report.txt
while IFS=: read -r f1 f2 f3 f4 f5 f6 f7
do 
	if [[ $f1 == "users"* || $f1 == "new_users"* ]] ; then
	 	echo "User $f1 with UID $f3 use $f7 shell and stores files in $f6 directory." >> pass_report.txt 
	fi
done < /etc/passwd


# part four
touch group_report.txt
while IFS=: read -r f1 f2 f3 f4
do
	if [[ $f1 == "group1" || $f1 == "group2" ]] ; then
	 	echo "Group -> $f1" >> group_report.txt 
	 	echo "GID -> $f3" >> group_report.txt 
	 	echo "Group List -> $f4" >> group_report.txt 
	fi
done < /etc/group

