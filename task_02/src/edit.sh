#!/bin/bash

script_path=$(realpath $0)
script_dir=$(dirname "$script_path")
cd "$script_dir"/../

log_file="$script_dir/files.log"

OK=0
ERR_PARAMS_NUM=1
ERR_NO_FILE=2
ERR_NO_RIGHTS=3

HELP_TEXT="Параметры: [filename] [str_1] [str_2]\n filename - путь к файлу\n str_1 - что заменить\n str_2 - на что заменить"

if [[ $# -ge 1 ]]
then
	if [[ "$1" == "-h" ]]
	then
		echo -e $HELP_TEXT
		exit $OK
	elif [[ "$1" == "--help" ]]
	then
		echo -e $HELP_TEXT
		exit $OK
	fi
fi

if [[ $# -ne 3 ]]
then
	echo "Неверное число параметров"
	exit $ERR_PARAMS_NUM
fi

file=$1
str_1=$2
str_2=$3

if ! [ -f "$file" ]
then
	echo "Файл не существует"
	exit $ERR_NO_FILE
fi

sed -i '' -e "s/$str_1/$str_2/g" "$file"

file_time=$(stat "$file" | awk '{print $8}')
file_size=$(stat -f "%Sm" -t "%Y-%m-%d %H:%M" "$file")
file_hash=$(shasum -a 256 "$file" | awk '{print $1}')
file_hash_mode="sha 256"

echo "$file - $file_time - $file_size - $file_hash -$file_hash_mode" >> "$log_file"
