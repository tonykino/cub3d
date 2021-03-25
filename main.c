#include "main.h"

const int map[13][20] = { \
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


void	init_data(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return ;//(1);
    data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Test");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return ;//(1);
	}
    data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    data->img.addr = mlx_get_data_addr(
						data->img.mlx_img, 
						&data->img.bpp, 
						&data->img.line_len, 
						&data->img.endian
					);	
}

void render_map(uint32_t *color_buffer, t_map *map_p)
{
	int i;
	int j;
	t_rect rect;

	i = 0;
	while (i < map_p->num_rows)
	{
		j = 0;
		while (j < map_p->num_cols)
		{
			rect.x = j * map_p->tile_size * MINIMAP_SCALE_FACTOR;
			rect.y = i * map_p->tile_size * MINIMAP_SCALE_FACTOR;
			rect.width = map_p->tile_size * MINIMAP_SCALE_FACTOR;
			rect.height = map_p->tile_size * MINIMAP_SCALE_FACTOR;

			if (map[i][j] == 0)
				rect.color = 0x00AAAAAA;
			else
				rect.color = 0x00123456;

			render_rectangle(color_buffer, &rect);

			j++;
		}
		i++;
	}
}

void render_rays(uint32_t *color_buffer, t_player *player, t_ray rays[NUM_RAYS])
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
		render_line(color_buffer, &line);
		i++;
	}
}

void render_player(uint32_t *color_buffer, t_player *player)
{
	t_rect player_rect;
	t_line player_line;

	player_rect.x = (player->x - player->width / 2) * MINIMAP_SCALE_FACTOR;
	player_rect.y = (player->y - player->height / 2) * MINIMAP_SCALE_FACTOR;
	player_rect.width = player->width * MINIMAP_SCALE_FACTOR;
	player_rect.height = player->height * MINIMAP_SCALE_FACTOR;
	player_rect.color = 0x00FFFF00;
	render_rectangle(color_buffer, &player_rect);

	player_line.x0 = player->x * MINIMAP_SCALE_FACTOR;
	player_line.y0 = player->y * MINIMAP_SCALE_FACTOR;
	player_line.x1 = (player->x + cos(player->rotation_angle) * 40) * MINIMAP_SCALE_FACTOR;
	player_line.y1 = (player->y + sin(player->rotation_angle) * 40) * MINIMAP_SCALE_FACTOR;
	player_line.color = 0x00FFFF00;
	render_line(color_buffer, &player_line);
}

void render_scene(t_data *data)
{
	render_map(data->color_buffer, &data->map_p);
	render_rays(data->color_buffer, &data->player, data->rays);
	render_player(data->color_buffer, &data->player);
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
	move_player(&data->player, &data->map_p);
	cast_all_rays(data);
}

int update_and_render(t_data *data)
{
	if (data->win_ptr == NULL)
		return 1;
	
	mlx_clear_window(data->mlx_ptr, data->win_ptr); // Useless ?
	// clear_img(&data->img);
	clear_color_buffer(data->color_buffer, 0x0000FFFF);

	update_scene(data);
	render_scene(data);
	
	copy_color_buffer_in_image(data->color_buffer, &data->img);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return 0;
}

void setup_player(t_player *player)
{
	player->x = WINDOW_WIDTH / 2;
	player->y = WINDOW_HEIGHT / 2;
	player->width = 12;
	player->height = 12;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = M_PI_2;
	player->walk_speed = 1;
	player->turn_speed = 2 * (M_PI / 180);
}

void setup_map(t_map *map_p)
{
	map_p->tile_size = 32;
	map_p->num_rows = 13;
	map_p->num_cols = 20;
}

void setup(t_data *data)
{
	setup_player(&data->player);
	setup_map(&data->map_p);
	data->color_buffer = (uint32_t*)ft_calloc(
		(uint32_t)WINDOW_WIDTH * (uint32_t)WINDOW_HEIGHT,
		sizeof(uint32_t)
	);
}

int             main(void)
{
	t_data data;

	init_data(&data);
    setup(&data);
	mlx_loop_hook(data.mlx_ptr, &update_and_render, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, 0);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
    mlx_loop(data.mlx_ptr);

	free(data.color_buffer);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);

	return(0);
}

// Pour tester le code :
// gcc -Llibmlx -Ilibmlx -lmlx -framework OpenGL -framework AppKit main.c && ./a.out