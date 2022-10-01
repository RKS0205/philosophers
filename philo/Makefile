SRC_FILES= main.c ft_atoi.c philo_actions.c free.c death_check.c thread.c init_list.c mutex_check.c
SRC=$(addprefix src/, $(SRC_FILES))
OBJ=$(addprefix obj/, $(SRC_FILES:.c=.o))
OBJ_DIR=obj
NAME=philo

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	gcc -Wall -Werror -Wextra -g -pthread $(OBJ) -o $(NAME)

obj/%.o: src/%.c
	gcc -Wall -Werror -Wextra -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
