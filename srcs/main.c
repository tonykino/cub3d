#include "main.h"

void render_scene(t_data *data)
{
	render_wall_projection(
		data->map.tile_size,
		data->player.rotation_angle,
		data->rays,
		data->textures
	);
	// render_sprite_projection(data->sprites, &data->map, &data->player, data->textures, data->rays);
	if (MINIMAP_SCALE_FACTOR > 0)
	{
		render_map_grid(&data->map);
		render_map_rays(&data->player, data->rays);
		render_map_sprites(data->sprites);
		render_map_player(&data->player);
	}

	copy_color_buffer_in_image(&data->window.win_img);
    mlx_put_image_to_window(get_mlx_ptr(), get_win_ptr(), data->window.win_img.mlx_img, 0, 0);
}

void update_scene(t_data *data)
{
	move_player(&data->player, &data->map);
	cast_all_rays(&data->player, data->rays, &data->map);
}

int update_and_render(t_data *data)
{
	if (no_window())
		return 1;
	
	// mlx_clear_window(data->mlx_ptr, data->win_ptr); // Useless ?
	// clear_img(&data->win_img);
	clear_color_buffer(0x00FFFFFF);

	update_scene(data);
	render_scene(data);
	
	return 0;
}

void setup(t_data *data)
{
	setup_map(&data->map);
	setup_player(&data->player, &data->map);
	setup_sprites(data->sprites);
	load_textures(data->textures);
}

int	main(int argc, char **argv)
{
	t_data data;

	system("clear && echo ---- Start Cub3D ----");
	init_cub3d(&data, argc, argv);

	setup(&data);
	mlx_mouse_hook(get_win_ptr(), mouse_hook, 0);
	mlx_hook(get_win_ptr(), KeyPress, KeyPressMask, &handle_keypress, &data.player);
	mlx_hook(get_win_ptr(), KeyRelease, KeyReleaseMask, &handle_keyrelease, &data.player);
	mlx_loop_hook(get_mlx_ptr(), &update_and_render, &data);
	mlx_loop(get_mlx_ptr());

	// // free_textures();
	// clear_mlx_data(data.win_img.mlx_img);
	printf("\n\n---- LEAKS ----\n");
	system("leaks --quiet a.out");
	return(0);
}
