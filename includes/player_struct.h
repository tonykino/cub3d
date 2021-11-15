/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:51:00 by tokino            #+#    #+#             */
/*   Updated: 2021/11/15 12:22:47 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_STRUCT_H
# define PLAYER_STRUCT_H

// PUBLIC API
typedef struct s_player {
	float	x;
	float	y;
	float	width;
	float	height;
	int		turn_direction;
	int		walk_direction;
	int		lateral_direction;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}	t_player;

#endif