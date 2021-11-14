/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:50:04 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 18:05:52 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include <float.h>

# include "constants.h"
# include "ray_struct.h"
# include "points_struct.h"
# include "graphics_struct.h"
# include "player_struct.h"
# include "map.h"

# define HORIZONTAL 1
# define VERTICAL 0


// PUBLIC API
void	cast_all_rays(t_player *player, t_ray *rays, t_map *map);
void	render_map_rays(t_map *map, t_player *player, \
	t_ray rays[NUM_RAYS], t_window *window);

// PRIVATE_API
typedef struct s_ray_hit {
	bool	hit;
	float	x;
	float	y;
	float	hit_dist;
	int		wall_content;
}	t_ray_hit;

void	cast_ray(t_ray *ray, t_player *player, t_map *map);
void	set_facing(t_ray *ray);

#endif
