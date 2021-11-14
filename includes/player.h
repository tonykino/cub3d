/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:35:18 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 23:25:25 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stdio.h>
# include <math.h>
# include <stdbool.h>

# include "constants.h"
# include "player_struct.h"
# include "map.h"
# include "graphics.h"
# include "libft.h"

// PUBLIC API
void	move_player(t_player *player, t_map *map, bool is_bonus);
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
