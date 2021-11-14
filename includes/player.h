/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:35:18 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 16:56:24 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stdio.h>
# include <math.h>
# include "constants.h"
# include "graphics.h"
# include "map.h"

// PUBLIC API
typedef struct s_player {
	float	x;
	float	y;
	float	width;
	float	height;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}	t_player;

void	move_player(t_player *player, t_map *map);
void	render_map_player(t_player *player, t_window *window);
void	setup_player(t_player *player, t_map *map);

// PRIVATE API
bool	bottom_touch(t_map *map, t_player *player, float new_y);
bool	left_touch(t_map *map, t_player *player, float new_x);
bool	right_touch(t_map *map, t_player *player, float new_x);
bool	top_touch(t_map *map, t_player *player, float new_y);

void	set_player_position(t_player *player, t_map *map);
void	set_player_orientation(t_player *player, char orientation);

#endif
