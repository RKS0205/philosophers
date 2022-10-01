SRC_FILES= main_bonus.c ft_atoi_bonus.c philo_actions_bonus.c free_bonus.c death_check_bonus.c \
			process_bonus.c init_list_bonus.c
SRC=$(addprefix src/, $(SRC_FILES))
OBJ=$(addprefix obj/, $(SRC_FILES:.c=.o))
OBJ_DIR=obj
NAME=philo_bonus

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
