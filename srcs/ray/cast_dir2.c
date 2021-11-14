/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_dir2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:01:01 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 19:10:21 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	set_hit_distance(t_player *player, t_ray_hit *rh, int tile_size)
{
	if (rh->hit)
		rh->hit_dist = dist_between_points(player->x, player->y, rh->x, rh->y);
	else
		rh->hit_dist = MAX_VIEW_DISTANCE * tile_size;
}

float	dist_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	set_perpendicular_coord(t_ray *ray, t_fpoint *touchs, bool direction)
{
	float	xy_opp;

	if (direction == HORIZONTAL)
	{
		if (ray->is_facing_up)
			xy_opp = touchs->y - 1;
		else
			xy_opp = touchs->y;
	}
	else
	{
		if (ray->is_facing_left)
			xy_opp = touchs->x - 1;
		else
			xy_opp = touchs->x;
	}
	return (xy_opp);
}

t_fpoint	sum_2_fpoints(t_fpoint a, t_fpoint b)
{
	t_fpoint	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

void	update_rh_and_nxt_touchs(t_ray_hit *rh, t_fpoint *ntouchs, t_map *map)
{
	rh->x = ntouchs->x;
	rh->y = ntouchs->y;
	ntouchs->x = floor(ntouchs->x / map->tile_size);
	ntouchs->y = floor(ntouchs->y / map->tile_size);
	rh->wall_content = get_content_at(map, ntouchs);
	rh->hit = true;
}
