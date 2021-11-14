/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:53:05 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 21:59:59 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	render_map_rays(t_map *map, t_player *player, t_ray *rays, \
	t_window *window)
{
	int		i;
	t_line	line;

	i = 0;
	while (i < window->width)
	{
		line.a.x = player->x * MINIMAP_SCALE_FACTOR;
		line.a.y = player->y * MINIMAP_SCALE_FACTOR;
		if (rays[i].wall_hit_x == 0.0 && rays[i].wall_hit_y == 0.0)
			set_no_hit_dest_coord(&line, &rays[i], map->tile_size);
		else
			set_hit_dest_coord(&line, &rays[i]);
		draw_line(window, &line);
		i++;
	}
}

void	set_no_hit_dest_coord(t_line *line, t_ray *ray, int tile_size)
{
	line->b.x = line->a.x + floor(MAX_VIEW_DISTANCE * tile_size * \
		MINIMAP_SCALE_FACTOR * cos(ray->angle));
	line->b.y = line->a.y + floor(MAX_VIEW_DISTANCE * tile_size * \
		MINIMAP_SCALE_FACTOR * sin(ray->angle));
	line->color = COLOR_PURPLE;
}

void	set_hit_dest_coord(t_line *line, t_ray *ray)
{
	line->b.x = floor(ray->wall_hit_x * MINIMAP_SCALE_FACTOR);
	line->b.y = floor(ray->wall_hit_y * MINIMAP_SCALE_FACTOR);
	if (ray->is_facing_right && ray->wall_hit_x != 0)
		line->b.x -= 1;
	if (ray->is_facing_down && ray->wall_hit_y != 0)
		line->b.y -= 1;
	line->color = COLOR_RED;
}
