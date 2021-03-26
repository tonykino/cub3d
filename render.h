#ifndef RENDER_H
# define RENDER_H

# include <stdbool.h>
# include <stdlib.h>
# include <mlx.h>
# include "struct.h"
# include "constants.h"

void clear_img(t_img *img);
bool pixel_is_out_of_screen(int x, int y);
void	img_pixel_put(t_img *img, int x, int y, int color);
void	render_rectangle(uint32_t *color_buffer, t_rect *rect);
void	render_line(uint32_t *color_buffer, t_line *line);
void	texel_put(uint32_t *texture, int x, int y, uint32_t color);
uint32_t get_texel_color(uint32_t *texture, int x, int y);
void	color_buffer_pixel_put(uint32_t *color_buffer, int x, int y, uint32_t color);
void clear_color_buffer(uint32_t *color_buffer, uint32_t color);
void copy_color_buffer_in_image(uint32_t *color_buffer, t_img *img);

#endif
