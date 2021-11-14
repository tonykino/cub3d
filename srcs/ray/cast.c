/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:39:42 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 22:33:30 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	cast_all_rays(t_window *window, t_player *player, \
	t_ray *rays, t_map *map)
{
	int		col;
	float	dist_proj_plane;

	dist_proj_plane = (window->width / 2) / tan(M_PI / 6);
	col = 0;
	while (col < window->width)
	{
		rays[col].angle = player->rotation_angle + \
			atan((col - window->width / 2) / dist_proj_plane);
		cast_ray(rays + col, player, map);
		col++;
	}
}

void	cast_ray(t_ray *ray, t_player *player, t_map *map)
{
	t_ray_hit	hray;
	t_ray_hit	vray;

	normalize_angle(&ray->angle);
	set_facing(ray);
	hray = cast_in_dir(ray, player, map, HORIZONTAL);
	vray = cast_in_dir(ray, player, map, VERTICAL);
	if (vray.hit_dist < hray.hit_dist)
	{
		copy_rh_in_ray(ray, &vray);
		ray->was_hit_vertical = true;
	}
	else
	{
		copy_rh_in_ray(ray, &hray);
		ray->was_hit_vertical = false;
	}
}

void	set_facing(t_ray *ray)
{
	if (ray->angle > 0 && ray->angle <= M_PI)
		ray->is_facing_down = true;
	else
		ray->is_facing_down = false;
	ray->is_facing_up = !ray->is_facing_down;
	if (ray->angle < M_PI_2 || ray->angle > M_PI + M_PI_2)
		ray->is_facing_right = true;
	else
		ray->is_facing_right = false;
	ray->is_facing_left = !ray->is_facing_right;
}

void	copy_rh_in_ray(t_ray *ray, t_ray_hit *rh)
{
	ray->distance = rh->hit_dist;
	ray->wall_hit_x = rh->x;
	ray->wall_hit_y = rh->y;
	ray->wall_hit_content = rh->wall_content;
}
