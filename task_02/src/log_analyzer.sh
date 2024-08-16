#!/bin/bash

script_path=$(realpath $0)
script_dir=$(dirname "$script_path")
cd "$script_dir"/../

OK=0
ERR_PARAMS_NUM=1
ERR_NO_FILE=2
ERR_NO_RIGHTS=3
ERR_WRONG_FILE=4

HELP_TEXT="Параметры: [filename] \n filename - путь к файлу\n"

if [[ $# -eq 1 ]]
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

if [[ $# -ne 1 ]]
then
        echo "Неверное число параметров"
        exit $ERR_PARAMS_NUM
fi

file=$1

if ! [ -f "$file" ]
then
        echo "Файл не существует"
        exit $ERR_NO_FILE
fi

if ! [[ "$file" =~ .*\.log$ ]]
then
	echo "Неправильный формат файла"
	exit $ERR_WRONG_FILE
fi 

logs_num=$(($(cat "$file" | wc -l)))
unique_files=$(($(cat "$file" | awk '{print $1}' | sort | uniq | wc -l)))
unique_hashes=$(($(cat "$file" | sort -s -k 1,1  | awk '{print $1"\ "$8}' | uniq | wc -l)))
changing_logs=$(($unique_hashes - $unique_files))

echo "$logs_num $unique_files $changing_logs"
exit $OK
