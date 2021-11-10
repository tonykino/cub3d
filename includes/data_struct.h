/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:48:21 by tokino            #+#    #+#             */
/*   Updated: 2021/11/10 15:48:46 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

# include <stdint.h>

# include "constants.h"
# include "texture.h"
# include "map.h"
# include "player.h"
# include "ray.h"

typedef struct s_data
{
	t_window	window;
	t_img		textures[NUM_TEXTURES];
	t_map		map;
	t_player	player;
	t_ray		rays[NUM_RAYS];
	uint32_t	ceil_color;
	uint32_t	floor_color;
}	t_data;

#endif