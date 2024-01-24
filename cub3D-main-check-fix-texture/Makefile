NAME	= cub3d

SRC		= 	main.c				\
			ft_utils_gnl.c		\
			ft_utils_split.c	\
			ft_utils_str_1.c	\
			ft_key.c			\
			ft_utils_convert.c			\
			ft_parsing.c \
			blend_color.c \

OBJ		= $(SRC:.c=.o)

FLAG	= cc -Wall -Wextra -Werror -g

RM		= rm -f

$(NAME): $(OBJ)
		$(FLAG) -Iinclude $(OBJ) -Llib -lmlx -lXext -lX11 -lm -o $(NAME)

all:	$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

val:	$(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./cub3d map.cub

.PHONY: all clean fclean re
