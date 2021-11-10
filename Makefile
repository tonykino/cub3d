SRC = 	$(addprefix srcs/, main.c \
		ray.c \
		graphics.c \
		hook.c \
		map.c \
		$(addprefix player/, setup.c move.c render.c) \
		texture.c \
		wall.c \
		libft.c \
		ft_atoi.c \
		ft_split.c \
		ft_strncmp.c \
		get_next_line.c \
		get_next_line_utils.c \
		initializer.c \
		clear_and_exit.c \
		parser.c)


HEADER	= $(addprefix -I , includes)

OBJ = $(SRC:.c=.o)

NAME = cub3D
CC = clang
CFLAGS = -Wall -Werror -Wextra

LINUX_DEP = -lXext -lX11

%.o:		%.c
			$(CC) $(CFLAGS) -c $< $(HEADER) -o $@

all: $(NAME)

$(NAME): libmlx.a $(OBJ)
	$(CC) -O3 -o $(NAME) $(OBJ) -L. -lm -lmlx $(LINUX_DEP)

libmlx.a:
	cd minilibx-linux && make
	mv minilibx-linux/libmlx.a ./
	cp minilibx-linux/mlx.h includes/

clean:
	rm -rf *.o
	rm -rf */*.o
	rm -rf */*/*.o

fclean:
	rm -f $(NAME)
	rm -f libmlx.a
	rm -f includes/mlx.h
	make clean
	cd minilibx-linux && make clean

re:
	make fclean
	make all

.PHONY: all clean fclean re