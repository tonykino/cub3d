#include "render.h"

void clear_img(t_img *img)
{
	int x;
	int y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{	
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			img_pixel_put(img, x, y, 0x000000);
			y++;
		}
		x++;
	}
}

bool pixel_is_out_of_screen(int x, int y)
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

	if (pixel_is_out_of_screen(x, y))
		return ;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int*)pixel = color;
}

void	color_buffer_pixel_put(uint32_t *color_buffer, int x, int y, uint32_t color)
{
	color_buffer[y * WINDOW_WIDTH + x] = color;
}

void	clear_color_buffer(uint32_t *color_buffer, uint32_t color)
{
	int i;
	int j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			color_buffer[j * WINDOW_WIDTH + i] = color;
			j++;
		}
		i++;
	}
}

void copy_color_buffer_in_image(uint32_t *color_buffer, t_img *img)
{
	int x;
	int y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			img_pixel_put(img, x, y, color_buffer[y * WINDOW_WIDTH + x]);
			y++;
		}
		x++;
	}
}

void	render_rectangle(uint32_t *color_buffer, t_rect *rect)
{
	int x;
	int y;

	x = rect->x;
	while(x < rect->x + rect->width)
	{
		y = rect->y;
		while(y < rect->y + rect->height)
		{
			color_buffer_pixel_put(color_buffer, x, y, rect->color);
			y++;
		}
		x++;
	}
}

void	render_line(uint32_t *color_buffer, t_line *line)
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
		color_buffer_pixel_put(color_buffer, line->x0, line->y0, line->color);
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
