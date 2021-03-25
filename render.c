#include "render.h"

bool pixel_is_out_of_screen(t_img *img, int x, int y)
{
	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

	if (pixel_is_out_of_screen(img, x, y))
		return ;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int*)pixel = color;
}


void	render_rectangle(t_img *img, t_rect *rect)
{
	int x;
	int y;

	x = rect->x;
	while(x < rect->x + rect->width)
	{
		y = rect->y;
		while(y < rect->y + rect->height)
		{
			img_pixel_put(img, x, y, rect->color);
			y++;
		}
		x++;
	}
}

void	render_line(t_img *img, t_line *line)
{
	int dx;
	int sx;
	int dy;
	int sy;
	int err;
	int e2;
 
	dx = abs(line->x1 - line->x0);
	sx = line->x0 < line->x1 ? 1 : -1;
	dy = -abs(line->y1 - line->y0);
	sy = line->y0 < line->y1 ? 1 : -1;
	err = dx + dy;
  	while (1)
	{
		img_pixel_put(img, line->x0, line->y0, line->color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			line->x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			line->y0 += sy;
		}
	}
}
