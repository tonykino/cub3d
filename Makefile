SRC = 	$(addprefix srcs/, main.c \
			$(addprefix parser/, parser.c resolution.c texture.c \
				ceil_floor_color.c map.c utilities.c) \
			$(addprefix graphics/, draw.c img_and_color_buffer.c) \
			$(addprefix player/, setup.c move.c render.c) \
			$(addprefix init/, init_cub3d.c init_data.c) \
			$(addprefix gnl/, get_next_line.c get_next_line_utils.c) \
			$(addprefix map/, map.c is_valid.c is_open.c) \
			$(addprefix ray/, cast.c cast_dir.c cast_dir2.c render.c) \
			hook.c \
			texture.c \
			wall.c \
			mlx_wrapper.c \
			clear_and_exit.c)

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