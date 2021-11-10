/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:27:06 by tokino            #+#    #+#             */
/*   Updated: 2021/11/10 14:27:48 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	move_player(t_player *player, t_map *map)
{
	float	move_step;
	float	new_x;
	float	new_y;

	player->rotation_angle += player->turn_direction * player->turn_speed;
	normalize_angle(&player->rotation_angle);
	move_step = player->walk_direction * player->walk_speed;
	new_x = player->x + cos(player->rotation_angle) * move_step;
	new_y = player->y + sin(player->rotation_angle) * move_step;
	if ((!left_touch(map, player, new_x) && new_x < player->x) || \
		(!right_touch(map, player, new_x) && new_x > player->x))
	{
		player->x = new_x;
	}
	if ((!top_touch(map, player, new_y) && new_y < player->y) || \
		(!bottom_touch(map, player, new_y) && new_y > player->y))
	{
		player->y = new_y;
	}
}

bool	left_touch(t_map *map, t_player *player, float new_x)
{
	float	x_to_test;

	x_to_test = new_x - player->width / 2;
	return (map_has_wall_at(map, x_to_test, player->y - player->height / 2) \
		|| map_has_wall_at(map, x_to_test, player->y + player->height / 2));
}

bool	right_touch(t_map *map, t_player *player, float new_x)
{
	float	x_to_test;

	x_to_test = new_x + player->width / 2;
	return (map_has_wall_at(map, x_to_test, player->y - player->height / 2) \
		|| map_has_wall_at(map, x_to_test, player->y + player->height / 2));
}

bool	top_touch(t_map *map, t_player *player, float new_y)
{
	float	y_to_test;

	y_to_test = new_y - player->width / 2;
	return (map_has_wall_at(map, player->x - player->width / 2, y_to_test) \
		|| map_has_wall_at(map, player->x + player->width / 2, y_to_test));
}

bool	bottom_touch(t_map *map, t_player *player, float new_y)
{
	float	y_to_test;

	y_to_test = new_y + player->width / 2;
	return (map_has_wall_at(map, player->x - player->width / 2, y_to_test) \
		|| map_has_wall_at(map, player->x + player->width / 2, y_to_test));
}
