/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:10:25 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 11:32:35 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear_and_exit.h" 

void	exit_on_error(t_data *data, char *err_msg)
{
	printf("Error\n%s\n", err_msg);
	cleanup_and_exit(data, -1);
}

void	clean_textures(t_window *window, t_img *textures)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		if (textures[i].path)
			free(textures[i].path);
		if (textures[i].name)
			free(textures[i].name);
		if (textures[i].mlx_img)
			mlx_destroy_image(window->mlx_ptr, textures[i].mlx_img);
		i++;
	}
}

void	clean_map(t_map *map)
{
	int i;

	if (map->grid)
	{
		i = 0;
		while (i < map->num_rows)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
}

void	cleanup(t_data *data)
{
	t_window	*window;

	window = &data->window;
	clean_textures(window, data->textures);
	clean_map(&data->map);
	if (window->color_buffer)
		free(window->color_buffer);
	if (window->win_img.mlx_img)
		mlx_destroy_image(window->mlx_ptr, window->win_img.mlx_img);
	if (window->win_ptr)
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	if (window->mlx_ptr)
	{
		mlx_destroy_display(window->mlx_ptr);
		free(window->mlx_ptr);
	}
}

void	cleanup_and_exit(t_data *data, int exit_status)
{
	cleanup(data);
	exit(exit_status);
}
