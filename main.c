#include "main.h"

void render_scene(t_data *data)
{
	render_wall_projection(
		data->map.tile_size,
		data->player.rotation_angle,
		data->rays,
		data->textures
	);
	// render_sprite_projection();
	render_map_grid(&data->map);
	render_map_rays(&data->player, data->rays);
	render_map_player(&data->player);

	copy_color_buffer_in_image(&data->win_img);
    mlx_put_image_to_window(get_mlx_ptr(), get_win_ptr(), data->win_img.mlx_img, 0, 0);
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
	load_textures(data->textures);
}

int	main(void)
{
	t_data data;

	init_mlx_data(&data.win_img);
    setup(&data);
	mlx_mouse_hook(get_win_ptr(), mouse_hook, 0);
	mlx_hook(get_win_ptr(), KeyPress, KeyPressMask, &handle_keypress, &data.player);
	mlx_hook(get_win_ptr(), KeyRelease, KeyReleaseMask, &handle_keyrelease, &data.player);
	mlx_loop_hook(get_mlx_ptr(), &update_and_render, &data);
    mlx_loop(get_mlx_ptr());

	// free_textures();
	clear_mlx_data(data.win_img.mlx_img);

	return(0);
}

// Pour tester le code :
// gcc -Wall -Werror -Wextra -Llibmlx -Ilibmlx -lmlx -framework OpenGL -framework AppKit main.c && ./a.out
