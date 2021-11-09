#include "ray.h"

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

void	set_hit_distance(t_player *player, t_ray_hit *rh)
{
	if (rh->hit)
		rh->hit_dist = dist_between_points(player->x, player->y, rh->x, rh->y);
	else
		rh->hit_dist = MAX_RAY_DISTANCE;
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

void	init_ray_hit(t_ray_hit *rh)
{
	rh->hit = false;
	rh->x = 0.0;
	rh->y = 0.0;
	rh->wall_content = 0;
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

void	update_rh_and_nxt_touchs(t_ray_hit *rh, t_fpoint *ntouchs, int tilesize)
{
	rh->x = ntouchs->x;
	rh->y = ntouchs->y;
	ntouchs->x = floor(ntouchs->x / tilesize);
	ntouchs->y = floor(ntouchs->y / tilesize);
	rh->wall_content = get_content_at(ntouchs);
	rh->hit = true;
}

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
			update_rh_and_nxt_touchs(&rh, &nxt_touchs, map->tile_size);
			break ;
		}
		else
			nxt_touchs = sum_2_fpoints(steps, nxt_touchs);
	}
	set_hit_distance(player, &rh);
	return (rh);
}

void	copy_rh_in_ray(t_ray *ray, t_ray_hit *rh)
{
	ray->distance = rh->hit_dist;
	ray->wall_hit_x = rh->x;
	ray->wall_hit_y = rh->y;
	ray->wall_hit_content = rh->wall_content;
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

void	cast_all_rays(t_player *player, t_ray *rays, t_map *map)
{
	int	col;

	col = 0;
	while (col < NUM_RAYS)
	{
		rays[col].angle = player->rotation_angle + \
			atan((col - NUM_RAYS / 2) / DIST_PROJ_PLANE);
		cast_ray(rays + col, player, map);
		col++;
	}
}

void	render_map_rays(t_player *player, t_ray rays[NUM_RAYS])
{
	int		i;
	t_line	line;

	i = 0;
	while (i < NUM_RAYS)
	{
		line.x0 = player->x * MINIMAP_SCALE_FACTOR;
		line.y0 = player->y * MINIMAP_SCALE_FACTOR;
		if (rays[i].wall_hit_x == 0.0 && rays[i].wall_hit_y == 0.0)
		{
			line.x1 = line.x0 + floor(MAX_RAY_DISTANCE * \
				MINIMAP_SCALE_FACTOR * cos(rays[i].angle));
			line.y1 = line.y0 + floor(MAX_RAY_DISTANCE * \
				MINIMAP_SCALE_FACTOR * sin(rays[i].angle));
			line.color = 0x00FF00FF;
		}
		else
		{
			line.x1 = floor(rays[i].wall_hit_x * MINIMAP_SCALE_FACTOR);
			line.y1 = floor(rays[i].wall_hit_y * MINIMAP_SCALE_FACTOR);
			line.color = 0x00FF0000;
		}
		draw_line(&line);
		i++;
	}
}
