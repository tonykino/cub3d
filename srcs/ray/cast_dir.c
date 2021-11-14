/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:57:22 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 18:59:52 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray_hit	cast_in_dir(t_ray *ray, t_player *player, t_map *map, bool dir)
{
	t_ray_hit	rh;
	t_fpoint	nxt_touchs;
	t_fpoint	steps;
	int			count;
	float		xy_opp;

	init_ray_hit(&rh);
	nxt_touchs = set_nxt_touchs(ray, player, map->tile_size, dir);
	steps = set_steps(ray, map->tile_size, dir);
	count = 0;
	while (is_inside_map(map, &nxt_touchs) || count < MAX_VIEW_DISTANCE)
	{
		count++;
		xy_opp = set_perpendicular_coord(ray, &nxt_touchs, dir);
		if ((dir == HORIZONTAL && map_has_wall_at(map, nxt_touchs.x, xy_opp)) \
			|| (dir == VERTICAL && map_has_wall_at(map, xy_opp, nxt_touchs.y)))
		{
			update_rh_and_nxt_touchs(&rh, &nxt_touchs, map);
			break ;
		}
		else
			nxt_touchs = sum_2_fpoints(steps, nxt_touchs);
	}
	set_hit_distance(player, &rh, map->tile_size);
	return (rh);
}

void	init_ray_hit(t_ray_hit *rh)
{
	rh->hit = false;
	rh->x = 0.0;
	rh->y = 0.0;
	rh->wall_content = 0;
}

t_fpoint	set_nxt_touchs(t_ray *ray, t_player *player, int tilesize, bool dir)
{
	t_fpoint	nxt_touchs;

	if (dir == HORIZONTAL)
	{
		nxt_touchs.y = floor(player->y / tilesize) * tilesize;
		if (ray->is_facing_down)
			nxt_touchs.y += tilesize;
		nxt_touchs.x = player->x + (nxt_touchs.y - player->y) / tan(ray->angle);
	}
	else
	{
		nxt_touchs.x = floor(player->x / tilesize) * tilesize;
		if (ray->is_facing_right)
			nxt_touchs.x += tilesize;
		nxt_touchs.y = player->y + (nxt_touchs.x - player->x) * tan(ray->angle);
	}
	return (nxt_touchs);
}

t_fpoint	set_steps(t_ray *ray, int tile_size, bool direction)
{
	t_fpoint	steps;

	if (direction == HORIZONTAL)
	{
		if (ray->is_facing_down)
			steps.y = tile_size;
		else
			steps.y = -1 * tile_size;
		steps.x = tile_size / tan(ray->angle);
		if ((steps.x > 0 && ray->is_facing_left) || \
			(steps.x < 0 && ray->is_facing_right))
			steps.x *= -1;
	}
	else
	{
		if (ray->is_facing_right)
			steps.x = tile_size;
		else
			steps.x = -1 * tile_size;
		steps.y = tile_size * tan(ray->angle);
		if ((steps.y > 0 && ray->is_facing_up) || \
			(steps.y < 0 && ray->is_facing_down))
			steps.y *= -1;
	}
	return (steps);
}
