# Name of the program
NAME = 21sh

SRC		=	main.c \
			unsetenv.c \
			echo_command.c \
			helper.c \
			run_command.c \
			cd_command.c \
			cd_command_2.c \
			get_env.c \
			helper_2.c \
			helper_3.c \
			lists_functions.c \
			exit.c \
			readterm.c \
			autocomplete.c \
			t_line_functions.c \
			history.c \
			fn_arrows.c\
			pipes.c\
			keycaps.c

OBJ		= $(SRC:.c=.o)

# CFLAGS	= -Wall -Wextra -Werror

CC		= gcc

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(OBJ) -ltermcap -o $(NAME) -L libft/ -lft
	@echo "\033[32m21sh: Built 21sh. (˘▾˘) \033[0m"

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ)
	@echo "\033[32m21sh: Cleaned up object files. (˘▾˘) \033[0m"

fclean: clean
	@$(MAKE) -C ./libft/ fclean
	@rm -rf $(NAME) $(OBJ)

re: fclean $(NAME)
