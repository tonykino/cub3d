/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:27:06 by tokino            #+#    #+#             */
/*   Updated: 2021/11/15 14:06:35 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	move_player(t_player *player, t_map *map, bool is_bonus)
{
	float	move_step;
	float	move_angle;
	float	new_x;
	float	new_y;

	player->rotation_angle += player->turn_direction * player->turn_speed;
	normalize_angle(&player->rotation_angle);
	move_step = set_move_step(player);
	move_angle = set_move_angle(player);
	new_x = player->x + cos(player->rotation_angle + move_angle) * move_step;
	new_y = player->y + sin(player->rotation_angle + move_angle) * move_step;
	if (!is_bonus || xside_touch(map, player, new_x))
	{
		player->x = new_x;
	}
	if (!is_bonus || yside_touch(map, player, new_y))
	{
		player->y = new_y;
	}
}

float	set_move_step(t_player *player)
{
	if (player->walk_direction != 0 || player->lateral_direction != 0)
		return (player->walk_speed);
	else
		return (0.0);
}

float	set_move_angle(t_player *player)
{
	if (player->walk_direction == -1)
		return (M_PI - player->lateral_direction * M_PI_4);
	else if (player->walk_direction == 1)
		return (player->lateral_direction * M_PI_4);
	else
		return (player->lateral_direction * M_PI_2);
}

bool	xside_touch(t_map *map, t_player *player, float new_x)
{
	float	x_min;
	float	x_max;

	x_min = new_x - player->width / 2;
	x_max = new_x + player->width / 2;
	return ((new_x < player->x \
			&& !(map_has_wall_at(map, x_min, player->y - player->height / 2) \
			|| map_has_wall_at(map, x_min, player->y + player->height / 2))) \
		|| (new_x > player->x \
			&& !(map_has_wall_at(map, x_max, player->y - player->height / 2) \
			|| map_has_wall_at(map, x_max, player->y + player->height / 2))));
}

bool	yside_touch(t_map *map, t_player *player, float new_y)
{
	float	y_min;
	float	y_max;

	y_min = new_y - player->width / 2;
	y_max = new_y + player->width / 2;
	return ((new_y < player->y \
			&& !(map_has_wall_at(map, player->x - player->width / 2, y_min) \
			|| map_has_wall_at(map, player->x + player->width / 2, y_min))) \
		|| (new_y > player->y \
			&& !(map_has_wall_at(map, player->x - player->width / 2, y_max) \
			|| map_has_wall_at(map, player->x + player->width / 2, y_max))));
}
