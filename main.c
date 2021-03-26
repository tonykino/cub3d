#include "main.h"

const int	grid[13][20] = { \
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} \
	};

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

void	render_map(t_map *map)
{
	int i;
	int j;
	t_rect rect;

	i = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			rect.x = j * map->tile_size * MINIMAP_SCALE_FACTOR;
			rect.y = i * map->tile_size * MINIMAP_SCALE_FACTOR;
			rect.width = map->tile_size * MINIMAP_SCALE_FACTOR;
			rect.height = map->tile_size * MINIMAP_SCALE_FACTOR;

			if (grid[i][j] == 0)
				rect.color = 0x00AAAAAA;
			else
				rect.color = 0x00123456;

			draw_rectangle(&rect);
			j++;
		}
		i++;
	}
}

void render_rays(t_player *player, t_ray rays[NUM_RAYS])
{
	int i;
	t_line line;

	i = 0;
	while (i < NUM_RAYS)
	{
		line.x0 = player->x * MINIMAP_SCALE_FACTOR;
		line.y0 = player->y * MINIMAP_SCALE_FACTOR;
		line.x1 = rays[i].wall_hit_x * MINIMAP_SCALE_FACTOR;
		line.y1 = rays[i].wall_hit_y * MINIMAP_SCALE_FACTOR;
		line.color = 0x00FF0000;
		draw_line(&line);
		i++;
	}
}

void render_player(t_player *player)
{
	t_rect player_rect;
	t_line player_line;

	player_rect.x = (player->x - player->width / 2) * MINIMAP_SCALE_FACTOR;
	player_rect.y = (player->y - player->height / 2) * MINIMAP_SCALE_FACTOR;
	player_rect.width = player->width * MINIMAP_SCALE_FACTOR;
	player_rect.height = player->height * MINIMAP_SCALE_FACTOR;
	player_rect.color = 0x00FFFF00;
	draw_rectangle(&player_rect);

	player_line.x0 = player->x * MINIMAP_SCALE_FACTOR;
	player_line.y0 = player->y * MINIMAP_SCALE_FACTOR;
	player_line.x1 = (player->x + cos(player->rotation_angle) * 40) * MINIMAP_SCALE_FACTOR;
	player_line.y1 = (player->y + sin(player->rotation_angle) * 40) * MINIMAP_SCALE_FACTOR;
	player_line.color = 0x00FFFF00;
	draw_line(&player_line);
}

void render_scene(t_data *data)
{
	render_3D_projection(data);
	// render_map(data->color_buffer, &data->map);
	// render_rays(data->color_buffer, &data->player, data->rays);
	// render_player(data->color_buffer, &data->player);

	copy_color_buffer_in_image(&data->img);
    mlx_put_image_to_window(get_mlx_ptr(), get_win_ptr(), data->img.mlx_img, 0, 0);
}

void move_player(t_player *player, t_map *map)
{
	float move_step;
	float new_player_x;
	float new_player_y;

	player->rotation_angle += player->turn_direction * player->turn_speed;
	move_step = player->walk_direction * player->walk_speed;
	new_player_x = player->x + cos(player->rotation_angle) * move_step;
	new_player_y = player->y + sin(player->rotation_angle) * move_step;


	if (!map_has_wall_at(map, new_player_x, new_player_y))
	{
		player->x = new_player_x;
		player->y = new_player_y;
	}
}

void update_scene(t_data *data)
{
	move_player(&data->player, &data->map);
	cast_all_rays(data);
}

int update_and_render(t_data *data)
{
	if (no_window())
		return 1;
	
	// mlx_clear_window(data->mlx_ptr, data->win_ptr); // Useless ?
	// clear_img(&data->img);
	clear_color_buffer(0x00FFFFFF);

	update_scene(data);
	render_scene(data);
	
	
	return 0;
}

void setup_player(t_player *player, t_map *map)
{
	player->x = map->num_cols * map->tile_size / 2;
	player->y = map->num_rows * map->tile_size / 2;
	player->width = 12;
	player->height = 12;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = M_PI_2;
	player->walk_speed = (float)map->tile_size / 32;
	player->turn_speed = 2 * (M_PI / 180);
}

void setup_map(t_map *map)
{
	map->tile_size = 1024;
	map->num_rows = 13;
	map->num_cols = 20;
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

	init_data(&data);
    setup(&data);
	mlx_mouse_hook(get_win_ptr(), mouse_hook, 0);
	mlx_hook(get_win_ptr(), KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(get_win_ptr(), KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop_hook(get_mlx_ptr(), &update_and_render, &data);
    mlx_loop(get_mlx_ptr());

	mlx_destroy_image(get_mlx_ptr(), data.img.mlx_img);

	return(0);
}

// Pour tester le code :
// gcc -Wall -Werror -Wextra -Llibmlx -Ilibmlx -lmlx -framework OpenGL -framework AppKit main.c && ./a.out
