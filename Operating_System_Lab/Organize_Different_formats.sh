#!/bin/bash

src=$1
dest=$2
if [ ! -e "$dest" ] ; then
    mkdir -p "$dest"
fi

shopt -s globstar
for filename in $src/**/*.*; do
	modified=$(date -r $filename "+%Y")
	compare="${filename##*.}"
	if [[ "${compare,,}" = "mp4" || "${compare,,}" = "avi" || "${compare,,}" = "3gp" || "${compare,,}" = "mpeg" || "${compare,,}" = "mkv" || "${compare,,}" = "wmv" || "${compare,,}" = "mov" ]]; then
		if [ ! -e "$dest/$modified" ] ; then
	   		mkdir "$dest/$modified"
		fi
		if [ ! -e "$dest/$modified/videos" ] ; then
	   		mkdir "$dest/$modified/videos"
		fi
		$(cp -p "$filename" "$dest/$modified/videos/${filename##*/}")
	fi
	
	if [[ "${compare,,}" = "jpg" || "${compare,,}" = "jpeg" || "${compare,,}" = "png" ]]; then

		if [ ! -e "$dest/$modified" ] ; then
	   		mkdir "$dest/$modified"
		fi
		if [ ! -e "$dest/$modified/photos" ] ; then
	   		mkdir "$dest/$modified/photos"
		fi
		width=$(identify -format '%w' $filename)
		if [[ $width -gt 1024 ]] ; then
			convert "$filename" -resize 1024x1024 "$dest/$modified/photos/${filename##*/}"
		else
			$(cp -p "$filename" "$dest/$modified/photos/${filename##*/}")
		fi
	fi
	
	
done


