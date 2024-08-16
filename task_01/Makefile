CC = gcc
FLAGS = -Wall -Werror -Wextra
BLD = ./build/
SRC = ./src/

$(BLD)%.o : $(SRC)%.c $(SRC)*.h
	$(CC) $(FLAGS) -c $< -o $@

strlen_tests : $(BLD)Quest1

$(BLD)Quest1 : $(BLD)s21_string.o $(BLD)s21_string_test.o
	$(CC) $(FLAGS) $^ -o $@