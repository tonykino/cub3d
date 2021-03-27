#include "player.h"

void render_map_player(t_player *player)
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

void setup_player(t_player *player, t_map *map)
{
	player->x = map->num_cols * map->tile_size / 2;
	player->y = map->num_rows * map->tile_size / 2;
	player->width = 12;
	player->height = 12;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = M_PI_2;
	player->walk_speed = 2 * (float)map->tile_size / 32;
	player->turn_speed = 2 * (M_PI / 180);
}
