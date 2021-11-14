/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:50:04 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 19:14:48 by tokino           ###   ########.fr       */
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
void		cast_all_rays(t_player *player, t_ray *rays, t_map *map);
void		render_map_rays(t_map *map, t_player *player, \
	t_ray rays[NUM_RAYS], t_window *window);

// PRIVATE_API
typedef struct s_ray_hit {
	bool	hit;
	float	x;
	float	y;
	float	hit_dist;
	int		wall_content;
}	t_ray_hit;

void		cast_ray(t_ray *ray, t_player *player, t_map *map);
void		set_facing(t_ray *ray);
void		copy_rh_in_ray(t_ray *ray, t_ray_hit *rh);

t_ray_hit	cast_in_dir(t_ray *ray, t_player *player, t_map *map, bool dir);
void		init_ray_hit(t_ray_hit *rh);
t_fpoint	set_nxt_touchs(t_ray *ray, t_player *player, int tilesize, \
	bool dir);
t_fpoint	set_steps(t_ray *ray, int tile_size, bool direction);
void		set_hit_distance(t_player *player, t_ray_hit *rh, int tile_size);
float		set_perpendicular_coord(t_ray *ray, t_fpoint *touchs, \
	bool direction);
t_fpoint	sum_2_fpoints(t_fpoint a, t_fpoint b);
void		update_rh_and_nxt_touchs(t_ray_hit *rh, t_fpoint *ntouchs, \
	t_map *map);
float		dist_between_points(float x1, float y1, float x2, float y2);

void		set_no_hit_dest_coord(t_line *line, t_ray *ray, int tile_size);
void		set_hit_dest_coord(t_line *line, t_ray *ray);

#endif
