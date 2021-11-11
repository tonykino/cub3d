/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:15:52 by tokino            #+#    #+#             */
/*   Updated: 2021/11/11 19:15:53 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	render_scene(t_data *data)
{
	render_wall_projection(data);
	if (MINIMAP_SCALE_FACTOR > 0)
	{
		render_map_grid(&data->map, &data->window);
		render_map_rays(&data->map, &data->player, data->rays, &data->window);
		render_map_player(&data->player, &data->window);
	}
	copy_color_buffer_in_image(&data->window);
	mlx_put_image_to_window(data->window.mlx_ptr, data->window.win_ptr, \
		data->window.win_img.mlx_img, 0, 0);
}

void	update_scene(t_data *data)
{
	move_player(&data->player, &data->map);
	cast_all_rays(&data->player, data->rays, &data->map);
}

int	update_and_render(t_data *data)
{
	if (no_window(&data->window))
		return (1);
	// mlx_clear_window(data->mlx_ptr, data->win_ptr); // Useless ?
	// clear_img(&data->win_img);
	clear_color_buffer(data->window.color_buffer);
	update_scene(data);
	render_scene(data);
	return (0);
}

void	setup(t_data *data)
{
	setup_map(&data->map);
	setup_player(&data->player, &data->map);
	load_textures(data->textures, &data->window);
}

int	main(int argc, char **argv)
{
	t_data	data;

	// system("clear && echo ---- Start Cub3D ----");
	init_cub3d(&data, argc, argv);
	setup(&data);
	mlx_mouse_hook(data.window.win_ptr, mouse_hook, 0);
	mlx_hook(data.window.win_ptr, 2, (1L << 0), &handle_keypress, &data.player);
	mlx_hook(data.window.win_ptr, 3, (1L << 1), &handle_keyrelease, &data);
	mlx_loop_hook(data.window.mlx_ptr, &update_and_render, &data);
	mlx_loop(data.window.mlx_ptr);
	cleanup_and_exit(&data, 0);
	return (0);
}
