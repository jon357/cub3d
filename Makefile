NAME	= cub3d

SRC		= 	main.c				\
			ft_utils_gnl.c		\
			ft_utils_split.c	\
			ft_utils_str_1.c	\
			ft_key.c			\
			ft_utils_convert.c			\

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

.PHONY: all clean fclean re
