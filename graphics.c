#include "graphics.h"

static uint32_t	*color_buffer = NULL;
static void		*mlx_ptr;
static void		*win_ptr;

// img_pixel related functions
static bool	pixel_is_out_of_screen(int x, int y)
{
	return (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT);
}

static void	img_pixel_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

	if (pixel_is_out_of_screen(x, y))
		return ;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int*)pixel = color;
}

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

void copy_color_buffer_in_image(t_img *img)
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

// color_buffer related functions

void	draw_pixel(int x, int y, uint32_t color)
{
	if (pixel_is_out_of_screen(x, y))
		return ;
	color_buffer[y * WINDOW_WIDTH + x] = color;
}

void	clear_color_buffer(uint32_t color)
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

// drawing functions

void	draw_rectangle(t_rect *rect)
{
	int x;
	int y;

	x = rect->x;
	while(x < rect->x + rect->width)
	{
		y = rect->y;
		while(y < rect->y + rect->height)
		{
			draw_pixel(x, y, rect->color);
			y++;
		}
		x++;
	}
}

void	draw_line(t_line *line)
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
		draw_pixel(line->x0, line->y0, line->color);
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

// mlx related functions

void	init_mlx_data(t_img *img)
{
	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return ;//(1);
    win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Test");
	if (win_ptr == NULL)
	{
		free(win_ptr);
		return ;//(1);
	}
    img->mlx_img = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    img->addr = mlx_get_data_addr(
						img->mlx_img, 
						&img->bpp, 
						&img->line_len, 
						&img->endian
					);	

	color_buffer = (uint32_t*)ft_calloc(
		(uint32_t)WINDOW_WIDTH * (uint32_t)WINDOW_HEIGHT,
		sizeof(uint32_t)
	);
}

// TODO LEGACY : manage to delete these getters

void *get_mlx_ptr(void)
{
	return (mlx_ptr);
}

void *get_win_ptr(void)
{
	return (win_ptr);
}

bool no_window(void)
{
	return (win_ptr == NULL);
}

void clear_mlx_data(void *mlx_img)
{
	mlx_destroy_image(mlx_ptr, mlx_img);
}