# read -p "Введите имя файла: " name
# echo ''

basename $1 .c

# echo 'Введите данный путь: cd /usr/local/lib '
# echo 'Затем эту : cd /usr/local/lib '


	#Стилевые тесты
# clang-format -n ""$1".c"
clang-format -i ""$1".c"
gcc -Wall -Werror -Wextra -std=c11 -o ""$1".exe" ""$1".c" #-fsanitize=address

cppcheck --enable=all --suppress=missingIncludeSystem ""$1".c"



	#Тест на утечки памяти

leaks -atExit -- "./"$1".exe"

#sh
#cd /usr/local/lib
#sudo ln -s /Applications/Xcode.app/Contents/Developer/usr/lib/libLeaksAtExit.dylib
	# или

# gcc -Wall -Werror -Wextra -std=c11 -o ""$1".exe" ""$1".c"  -fsanitize=leak
	# или
# gcc -Wall -Werror -Wextra -std=c11 -o ""$1".exe" ""$1".c"  # "$name" "$path" -fsanitize=undefined
	# или
# gcc -Wall -Werror -Wextra -std=c11 -o ""$1".exe" ""$1".c"  # "$name" "$path" -fsanitize=unreachable