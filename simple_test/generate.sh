#!/bin/sh

#fname=`basename $1`
file=$1
fname_wo_ext=${file%[.]*}
fext=${file##*.}

echo $fname_wo_ext
echo $fext

cog.py -o ${fname_wo_ext} ${file}