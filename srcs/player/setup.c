/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:31:25 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 16:59:16 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	setup_player(t_player *player, t_map *map)
{
	set_player_position(player, map);
	player->width = map->tile_size / 2;
	player->height = map->tile_size / 2;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->walk_speed = (float)map->tile_size / 16;
	player->turn_speed = M_PI / 90;
}

void	set_player_position(t_player *player, t_map *map)
{
	int row;
	int col;
	bool found_player;

	row = 0;
	found_player = false;
	while (found_player == false && row < map->num_rows)
	{
		col = 0;
		while (found_player == false && col < map->num_cols)
		{
			if (ft_strchr("NSEW", map->grid[row][col]))
			{
				found_player = true;
				player->x = (float)(col + 0.5) * map->tile_size;
				player->y = (float)(row + 0.5) * map->tile_size;
				set_player_orientation(player, map->grid[row][col]);
				map->grid[row][col] = '0';
			}
			col++;
		}
		row++;
	}
}

void	set_player_orientation(t_player *player, char orientation)
{
	if (orientation == 'S')
		player->rotation_angle = M_PI_2;
	else if (orientation == 'W')
		player->rotation_angle = M_PI;
	else if (orientation == 'N')
		player->rotation_angle = M_PI_2 + M_PI;
	else if (orientation == 'E')
		player->rotation_angle = 2.0 * M_PI;
}