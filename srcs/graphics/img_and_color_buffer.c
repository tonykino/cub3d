/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_and_color_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:34:16 by tokino            #+#    #+#             */
/*   Updated: 2021/11/12 14:39:03 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

// img_pixel related functions
static bool	pixel_is_out_of_screen(int x, int y)
{
	return (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT);
}

void	copy_color_buffer_in_image(t_window *window)
{
	int		x;
	int		y;
	char	*pixel;
	t_img	*img;

	img = &window->win_img;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
			*(int *)pixel = window->color_buffer[y * WINDOW_WIDTH + x];
			y++;
		}
		x++;
	}
}

// color_buffer related functions
bool	is_transparent(uint32_t color)
{
	return ((color & 0xFF000000) == 0xFF000000);
}

void	draw_pixel(int x, int y, uint32_t color, uint32_t *color_buffer)
{
	if (pixel_is_out_of_screen(x, y) || is_transparent(color))
		return ;
	color_buffer[y * WINDOW_WIDTH + x] = color;
}

void	clear_color_buffer(uint32_t *color_buffer)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			color_buffer[j * WINDOW_WIDTH + i] = COLOR_BLACK;
			j++;
		}
		i++;
	}
}
