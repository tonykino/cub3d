#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <stdbool.h>
# include <stdlib.h>
# include <mlx.h>
# include "struct.h"
# include "constants.h"
# include "libft.h"

void	clear_img(t_img *img);
void	draw_rectangle(t_rect *rect);
void	draw_line(t_line *line);
void	draw_pixel(int x, int y, uint32_t color);
void	clear_color_buffer(uint32_t color);
void	copy_color_buffer_in_image(t_img *img);
void	init_data(t_data *data);
void	*get_mlx_ptr(void);
void	*get_win_ptr(void);
bool	no_window(void);

#endif
