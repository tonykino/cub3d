#ifndef RENDER_H
# define RENDER_H

# include <stdbool.h>
# include <stdlib.h>
# include <mlx.h>
# include "struct.h"
# include "constants.h"


bool pixel_is_out_of_screen(t_img *img, int x, int y);
void	img_pixel_put(t_img *img, int x, int y, int color);
void	render_rectangle(t_img *img, t_rect *rect);
void	render_line(t_img *img, t_line *line);

#endif
