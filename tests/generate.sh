#!/bin/sh

#fname=`basename $1`
file=$1
config_file=${file}
fname_wo_ext=${file%[.]*}
cpp_file=${fname_wo_ext}.cpp
h_file=${fname_wo_ext}.h
#fext=${file##*.}

echo "Generating class" ${fname_wo_ext}
echo "Reading config from : " ${config_file}
#echo $fext


echo "Generating " ${cpp_file} 
cog.py -o ${cpp_file} -D CONFIG_FILE=${config_file} -d -z ../templates/CppFile.cog
echo "Generating " ${h_file} 
cog.py -o ${h_file} -D CONFIG_FILE=${config_file} -d -z ../templates/HFile.cog

echo "done."
