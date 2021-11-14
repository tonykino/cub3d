/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:40:14 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 18:13:12 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_wrapper.h"

void	init_mlx_data(t_data *data, t_window *window)
{
	t_img	*img;

	img = &window->win_img;
	window->mlx_ptr = mlx_init();
	if (window->mlx_ptr == NULL)
		exit_on_error(data, "Failed MLX initialisation.");
	window->win_ptr = mlx_new_window(window->mlx_ptr, WINDOW_WIDTH, \
		WINDOW_HEIGHT, "Cub3D");
	if (window->win_ptr == NULL)
		exit_on_error(data, "Failed MLX window creation.");
	img->mlx_img = mlx_new_image(window->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (img->mlx_img == NULL)
		exit_on_error(data, "Failed MLX img creation.");
	img->addr = mlx_get_data_addr(
			img->mlx_img,
			&img->bpp,
			&img->line_len,
			&img->endian
			);
	window->color_buffer = (uint32_t *)ft_calloc(
			(uint32_t)WINDOW_WIDTH * (uint32_t)WINDOW_HEIGHT,
			sizeof(uint32_t)
			);
	if (window->color_buffer == NULL)
		exit_on_error(data, "Failed color_buffer malloc.");
}

bool	no_window(t_window *window)
{
	return (window->win_ptr == NULL);
}
