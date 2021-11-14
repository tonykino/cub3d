/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:48:21 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 23:25:40 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

# include <stdint.h>
# include <stdbool.h>

# include "constants.h"
# include "graphics_struct.h"
# include "player_struct.h"
# include "map_struct.h"
# include "ray_struct.h"

typedef struct s_data
{
	t_window	window;
	t_img		textures[NUM_TEXTURES];
	t_map		map;
	t_player	player;
	t_ray		*rays;
	uint32_t	ceil_color;
	uint32_t	floor_color;
	bool		is_bonus;
}	t_data;

#endif
