/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:40:14 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 23:08:59 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_wrapper.h"

void	init_mlx_data(t_data *data, t_window *win)
{
	t_img	*img;

	img = &win->win_img;
	win->mlx_ptr = mlx_init();
	if (win->mlx_ptr == NULL)
		exit_on_error(data, "Failed MLX initialisation.");
	resize_window_if_needed(win);
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->width, \
		win->height, "Cub3D");
	if (win->win_ptr == NULL)
		exit_on_error(data, "Failed MLX window creation.");
	img->mlx_img = mlx_new_image(win->mlx_ptr, win->width, win->height);
	if (img->mlx_img == NULL)
		exit_on_error(data, "Failed MLX img creation.");
	img->addr = mlx_get_data_addr(
			img->mlx_img,
			&img->bpp,
			&img->line_len,
			&img->endian);
	win->color_buffer = (uint32_t *)ft_calloc(
			(uint32_t)win->width * (uint32_t)win->height,
			sizeof(uint32_t));
	if (win->color_buffer == NULL)
		exit_on_error(data, "Failed color_buffer malloc.");
}

bool	no_window(t_window *window)
{
	return (window->win_ptr == NULL);
}

void	resize_window_if_needed(t_window *window)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(window->mlx_ptr, &screen_width, &screen_height);
	if (window->width > screen_width)
	{
		window->width = screen_width;
		window->win_img.width = screen_width;
	}
	if (window->height > screen_height)
	{
		window->height = screen_height;
		window->win_img.height = screen_height;
	}
}
