#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <stdbool.h>
# include <stdlib.h>
# include <mlx.h>
# include "struct.h"
# include "constants.h"
# include "libft.h"

typedef struct  s_img {
    void	*mlx_img;
    char	*addr;
	char	*path;
    int		bpp;
    int		line_len;
    int		endian;
	int 	width;
	int 	height;
}	t_img;

typedef struct s_rect {
	int x;
	int y;
	int width;
	int height;
	int color;
}	t_rect;

typedef struct s_line {
	int x0;
	int y0;
	int x1;
	int y1;
	int color;
}	t_line;

void	clear_img(t_img *img);
void	draw_rectangle(t_rect *rect);
void	draw_line(t_line *line);
void	draw_pixel(int x, int y, uint32_t color);
void	clear_color_buffer(uint32_t color);
void	copy_color_buffer_in_image(t_img *img);
void	init_mlx_data(t_img *img);
void	*get_mlx_ptr(void);
void	*get_win_ptr(void);
void	clear_mlx_data(void *mlx_img);
bool	no_window(void);

#endif
