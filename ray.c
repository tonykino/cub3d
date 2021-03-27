#include "ray.h"

static float normalize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
	{
		angle += 2 * M_PI;
	}
	return (angle);
}

static float distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void cast_ray(float ray_angle, t_ray *ray, t_player *player, t_map *map)
{
	ray->ray_angle = normalize_angle(ray_angle);

	if (ray->ray_angle > 0 && ray->ray_angle <= M_PI)
		ray->is_facing_down = true;
	else
		ray->is_facing_down = false;
	ray->is_facing_up = !ray->is_facing_down;

	if (ray->ray_angle < M_PI_2 || ray->ray_angle > M_PI + M_PI_2)
		ray->is_facing_right = true;
	else
		ray->is_facing_right = false;
	ray->is_facing_left = !ray->is_facing_right;

	float xintercept;
	float yintercept;
	float xstep;
	float ystep;


	// HORZ PART
	bool found_horz_wall_hit = false;
	float horz_wall_hit_x = 0.0;
	float horz_wall_hit_y = 0.0;
	float next_horz_touch_x;
	float next_horz_touch_y;
	int horz_wall_content = 0;

	yintercept = floor(player->y / map->tile_size) * map->tile_size;
	if (ray->is_facing_down)
		yintercept += map->tile_size;

	xintercept = player->x + (yintercept - player->y) / tan(ray->ray_angle);

	if (ray->is_facing_down)
		ystep = map->tile_size;
	else
		ystep = -1 * map->tile_size;

	xstep = map->tile_size / tan(ray->ray_angle);
	if ((xstep > 0 && ray->is_facing_left) || (xstep < 0 && ray->is_facing_right))
		xstep *= -1;

	next_horz_touch_x = xintercept;
	next_horz_touch_y = yintercept;

	while (is_inside_map(map, next_horz_touch_x, next_horz_touch_y))
	// while(next_horz_touch_x >= 0 && (next_horz_touch_x < map->num_cols * map->tile_size) && next_horz_touch_y >= 0 && (next_horz_touch_y < map->num_rows * map->tile_size))
	{
		float y_to_check;

		if (ray->is_facing_up)
			y_to_check = next_horz_touch_y - 1;
		else
			y_to_check = next_horz_touch_y;

		if (map_has_wall_at(map, next_horz_touch_x, y_to_check))
		{
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			next_horz_touch_y = floor(next_horz_touch_y / map->tile_size);
			next_horz_touch_x = floor(next_horz_touch_x / map->tile_size);
			horz_wall_content = get_content_at((int)next_horz_touch_x, (int)next_horz_touch_y);
			found_horz_wall_hit = true;
			break;
		}
		else
		{
			next_horz_touch_x += xstep;
			next_horz_touch_y += ystep;
		}
	}

	// VERT PART
	bool found_vert_wall_hit = false;
	float vert_wall_hit_x = 0.0;
	float vert_wall_hit_y = 0.0;
	float next_vert_touch_x;
	float next_vert_touch_y;
	int vert_wall_content = 0;

	xintercept = floor(player->x / map->tile_size) * map->tile_size;
	if (ray->is_facing_right)
		xintercept += map->tile_size;

	yintercept = player->y + (xintercept - player->x) * tan(ray->ray_angle);

	if (ray->is_facing_right)
		xstep = map->tile_size;
	else
		xstep = -1 * map->tile_size;

	ystep = map->tile_size * tan(ray->ray_angle);
	if ((ystep > 0 && ray->is_facing_up) || (ystep < 0 && ray->is_facing_down))
		ystep *= -1;

	next_vert_touch_x = xintercept;
	next_vert_touch_y = yintercept;

	while (is_inside_map(map, next_vert_touch_x, next_vert_touch_y))
	// while(next_vert_touch_x >= 0 && (next_vert_touch_x < map->num_cols * map->tile_size) && next_vert_touch_y >= 0 && (next_vert_touch_y < map->num_rows * map->tile_size))
	{
		float x_to_check;
		
		if (ray->is_facing_left)
			x_to_check = next_vert_touch_x - 1;
		else
			x_to_check = next_vert_touch_x;

		if (map_has_wall_at(map, x_to_check, next_vert_touch_y))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			next_vert_touch_y = floor(next_vert_touch_y / map->tile_size);
			next_vert_touch_x = floor(next_vert_touch_x / map->tile_size);
			vert_wall_content = get_content_at((int)next_vert_touch_x, (int)next_vert_touch_y);
			found_vert_wall_hit = true;
			break;
		}
		else
		{
			next_vert_touch_x += xstep;
			next_vert_touch_y += ystep;
		}
	}

	// Calculate both horz and vert hit distances and choose the smallest one
	float horz_hit_distance;
	float vert_hit_distance;

	if (found_horz_wall_hit)
		horz_hit_distance = distance_between_points(player->x, player->y, horz_wall_hit_x, horz_wall_hit_y);
	else
		horz_hit_distance = FLT_MAX;
	
	if (found_vert_wall_hit)
		vert_hit_distance = distance_between_points(player->x, player->y, vert_wall_hit_x, vert_wall_hit_y);
	else
		vert_hit_distance = FLT_MAX;

	if (vert_hit_distance < horz_hit_distance)
	{
		ray->distance = vert_hit_distance;
		ray->wall_hit_x = vert_wall_hit_x;
		ray->wall_hit_y = vert_wall_hit_y;
		ray->wall_hit_content = vert_wall_content;
		ray->was_hit_vertical = true;
	}
	else
	{
		ray->distance = horz_hit_distance;
		ray->wall_hit_x = horz_wall_hit_x;
		ray->wall_hit_y = horz_wall_hit_y;
		ray->wall_hit_content = horz_wall_content;
		ray->was_hit_vertical = false;
	}
}

void cast_all_rays(t_player *player, t_ray *rays, t_map *map)
{
	float ray_angle;
	int col;

	col = 0;
	while (col < NUM_RAYS)
	{
		ray_angle = player->rotation_angle + atan((col - NUM_RAYS / 2) / DIST_PROJ_PLANE);
		cast_ray(ray_angle, rays + col, player, map);
		col++;
	}
}

void render_rays(t_player *player, t_ray rays[NUM_RAYS])
{
	int i;
	t_line line;

	i = 0;
	while (i < NUM_RAYS)
	{
		line.x0 = player->x * MINIMAP_SCALE_FACTOR;
		line.y0 = player->y * MINIMAP_SCALE_FACTOR;
		line.x1 = rays[i].wall_hit_x * MINIMAP_SCALE_FACTOR;
		line.y1 = rays[i].wall_hit_y * MINIMAP_SCALE_FACTOR;
		line.color = 0x00FF0000;
		draw_line(&line);
		i++;
	}
}
