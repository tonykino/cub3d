/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:40:14 by tokino            #+#    #+#             */
/*   Updated: 2021/11/12 15:55:07 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	init_mlx_data(t_window *window)
{
	t_img	*img;

	img = &window->win_img;
	window->mlx_ptr = mlx_init();
	if (window->mlx_ptr == NULL)
		return ;// TODO 
	window->win_ptr = mlx_new_window(window->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (window->win_ptr == NULL)
	{
		free(window->win_ptr);
		return ;// TODO
	}
	img->mlx_img = mlx_new_image(window->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	img->addr = mlx_get_data_addr(
			img->mlx_img,
			&img->bpp,
			&img->line_len,
			&img->endian
			);
	// TODO handle new_img & get data addr errors
	window->color_buffer = (uint32_t *)ft_calloc(
			(uint32_t)WINDOW_WIDTH * (uint32_t)WINDOW_HEIGHT,
			sizeof(uint32_t)
			);
	// TODO handle calloc error
}

bool	no_window(t_window *window)
{
	return (window->win_ptr == NULL);
}
