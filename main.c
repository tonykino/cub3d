#include "main.h"

void	render_3D_projection(t_data *data)
{
	t_map *map = &data->map;
	t_player *player = &data->player;
	t_ray *rays = data->rays;
	t_img *texture;
	int x;
	int y;
	float projected_wall_height;
	float corrected_distance;
	int wall_top_pixel;
	int wall_bottom_pixel;
	uint32_t color;

	x = 0;
	while (x < NUM_RAYS)
	{
		corrected_distance = rays[x].distance * cos(rays[x].ray_angle - player->rotation_angle);
		projected_wall_height = (map->tile_size / corrected_distance) * DIST_PROJ_PLANE;

		wall_top_pixel = (WINDOW_HEIGHT / 2) - ((int)projected_wall_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;

		wall_bottom_pixel = wall_top_pixel + (int)projected_wall_height;
		if (wall_bottom_pixel >= WINDOW_HEIGHT)
			wall_bottom_pixel = WINDOW_HEIGHT - 1;

		int texture_offset_x;
		if (rays[x].was_hit_vertical)
		{
			texture_offset_x = (int)rays[x].wall_hit_y % map->tile_size;
			if (rays[x].is_facing_right)
				texture = &data->textures[0];
			else
				texture = &data->textures[1];
		}
		else
		{
			texture_offset_x = (int)rays[x].wall_hit_x % map->tile_size;
			if (rays[x].is_facing_up)
				texture = &data->textures[2];
			else
				texture = &data->textures[3];
		}
		texture_offset_x *= (float)texture->width / map->tile_size;

		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			int texture_offset_y;

			if (y < wall_top_pixel)
			{
				color = 0x0087CEEB;
			}
			else if (y < wall_bottom_pixel)
			{
				texture_offset_y = (int)((float)(y - (WINDOW_HEIGHT / 2) + ((int)projected_wall_height / 2)) * texture->height / projected_wall_height);
				color = get_texel_color(texture, texture_offset_x, texture_offset_y);
			}
			else 
			{
				color = 0x008B5A2B;
			}
			draw_pixel(x, y, color);
			y++;
		}
		x++;
	}
}

void render_scene(t_data *data)
{
	render_3D_projection(data);
	render_map(&data->map);
	render_rays(&data->player, data->rays);
	render_player(&data->player);

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

	clear_mlx_data(data.win_img.mlx_img);

	return(0);
}

// Pour tester le code :
// gcc -Wall -Werror -Wextra -Llibmlx -Ilibmlx -lmlx -framework OpenGL -framework AppKit main.c && ./a.out
