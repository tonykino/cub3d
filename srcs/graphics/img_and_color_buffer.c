/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_and_color_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:34:16 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 20:53:27 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

// img_pixel related functions
static bool	pixel_is_out_of_screen(t_window *window, int x, int y)
{
	return (x < 0 || x >= window->width || y < 0 || y >= window->height);
}

void	copy_color_buffer_in_image(t_window *window)
{
	int		x;
	int		y;
	char	*pixel;
	t_img	*img;

	img = &window->win_img;
	x = 0;
	while (x < window->width)
	{
		y = 0;
		while (y < window->height)
		{
			pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
			*(int *)pixel = window->color_buffer[y * window->width + x];
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

void	draw_pixel(t_window *window, int x, int y, uint32_t color)
{
	if (pixel_is_out_of_screen(window, x, y) || is_transparent(color))
		return ;
	window->color_buffer[y * window->width + x] = color;
}

void	clear_color_buffer(t_window *window)
{
	int	i;
	int	j;

	i = 0;
	while (i < window->width)
	{
		j = 0;
		while (j < window->height)
		{
			window->color_buffer[j * window->width + i] = COLOR_BLACK;
			j++;
		}
		i++;
	}
}
