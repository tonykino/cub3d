SRC = 	$(addprefix srcs/, main.c \
		ray.c \
		$(addprefix graphics/, draw.c img_and_color_buffer.c mlx_wrapper.c) \
		hook.c \
		map.c \
		$(addprefix player/, setup.c move.c render.c) \
		texture.c \
		wall.c \
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

$(NAME): libft.a libmlx.a $(OBJ)
	$(CC) -O3 -o $(NAME) $(OBJ) -L. -lm -lft -lmlx $(LINUX_DEP)

libft.a:
	$(MAKE) -C libft
	mv libft/libft.a ./
	cp libft/libft.h includes/

libmlx.a:
	$(MAKE) -C minilibx-linux
	mv minilibx-linux/libmlx.a ./
	cp minilibx-linux/mlx.h includes/

clean:
	rm -rf *.o
	rm -rf */*.o
	rm -rf */*/*.o

fclean:
	rm -f $(NAME)
	rm -f libft.a
	rm -f libmlx.a
	rm -f includes/libft.h
	rm -f includes/mlx.h
	make clean
	$(MAKE) fclean -C libft
	$(MAKE) clean -C minilibx-linux

re:
	make fclean
	make all

.PHONY: all clean fclean re