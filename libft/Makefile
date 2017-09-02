# Name of the library
NAME = libft.a

# Compiling flags
FLAGS = -Wall -Wextra -Werror

# Source files and object files
SRC = ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strdup.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strstr.c \
		ft_strnstr.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strsplit.c \
		ft_itoa.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstaddback.c\
		ft_swap.c\
		ft_div_mod.c\
		ft_generic.c\
		ft_isspace.c\
		ft_sqrt.c\
		ft_memset.c\
		get_next_line.c\
		ft_printf_color.c\
		ft_printf_basic.c\
		ft_putmatrix.c\
		ft_free_mtx.c\
		ft_cursor_goto.c\
		ft_termcmd.c\
		ft_clrscreen.c\
		ft_error.c
OBJ = $(SRC:.c=.o)

# all rule
all: $(NAME)

%.o:%.c
	@gcc $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "[INFO] Library [$(NAME)] created!"

# clean rule
clean:
	@rm -f $(OBJ)
	@echo "[INFO] Objects removed!"

# fclean rule
fclean: clean
	@rm -f $(NAME)
	@echo "[INFO] Library [$(NAME)] removed!"

# re rule
re:	fclean all

# phony
.PHONY: all, clean, fclean, re
