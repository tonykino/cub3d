/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:31:25 by tokino            #+#    #+#             */
/*   Updated: 2021/11/10 14:33:39 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	setup_player(t_player *player, t_map *map)
{
	player->x = map->num_cols * map->tile_size / 2; // TODO parsing
	player->y = map->num_rows * map->tile_size / 2; // TODO parsing
	player->width = map->tile_size / 2;
	player->height = map->tile_size / 2;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = M_PI_2; // TODO parsing
	player->walk_speed = (float)map->tile_size / 16;
	player->turn_speed = M_PI / 90;
}
