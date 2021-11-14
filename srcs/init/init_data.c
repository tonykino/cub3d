/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:54:14 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 13:58:12 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	init_all_data(t_data *data)
{
	init_window(&data->window);
	init_textures(data->textures);
	data->ceil_color = 0;
	data->floor_color = 0;
	init_map(&data->map);
}

void	init_window(t_window *window)
{
	window->mlx_ptr = NULL;
	window->win_ptr = NULL;
	window->color_buffer = NULL;
	init_img(&window->win_img);
	window->width = 0;
	window->height = 0;
}

void	init_textures(t_img *textures)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		init_img(textures + i);
		i++;
	}
}

void	init_img(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->path = NULL;
	img->name = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

void	init_map(t_map *map)
{
	map->tile_size = 1024;
	map->num_rows = 0;
	map->num_cols = 0;
	map->grid = NULL;
}
