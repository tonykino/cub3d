/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:09:24 by tokino            #+#    #+#             */
/*   Updated: 2021/11/12 22:28:57 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	render_wall_projection(t_data *data)
{
	int			x;
	int			y;
	t_wall		wall;
	int			texture_offset_x;
	uint32_t	color;

	x = 0;
	while (x < NUM_RAYS)
	{
		wall = set_wall(&data->rays[x], data->player.rotation_angle, \
			data->map.tile_size);
		wall.texture = get_wall_texture(data->textures, &data->rays[x]);
		texture_offset_x = set_tex_offset_x(wall.texture, &data->rays[x], \
			data->map.tile_size);
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			color = get_color(data, y, &wall, texture_offset_x);
			draw_pixel(x, y, color, data->window.color_buffer);
			y++;
		}
		x++;
	}
}

t_wall	set_wall(t_ray *ray, float player_rot_angle, int tilesize)
{
	t_wall	wall;
	float	perp_distance;
	float	dist_proj_plane;

	if (ray->wall_hit_x == 0.0 && ray->wall_hit_y == 0.0)
	{
		wall.height = 0.0;
	}
	else
	{
		perp_distance = ray->distance * cos(ray->angle - player_rot_angle);
		dist_proj_plane = (WINDOW_WIDTH / 2) / tan(M_PI / 6);
		wall.height = (int)(tilesize * dist_proj_plane / perp_distance);
	}
	wall.top = (WINDOW_HEIGHT / 2) - (wall.height / 2);
	if (wall.top < 0)
		wall.top = 0;
	wall.bottom = wall.top + (int)wall.height;
	if (wall.bottom >= WINDOW_HEIGHT)
		wall.bottom = WINDOW_HEIGHT - 1;
	return (wall);
}

t_img	*get_wall_texture(t_img *textures, t_ray *ray)
{
	if (ray->was_hit_vertical)
	{
		if (ray->is_facing_right)
			return (get_texture(textures, "EA"));
		else
			return (get_texture(textures, "WE"));
	}
	else
	{
		if (ray->is_facing_up)
			return (get_texture(textures, "NO"));
		else
			return (get_texture(textures, "SO"));
	}	
}

int	set_tex_offset_x(t_img *texture, t_ray *ray, int tilesize)
{
	int	texture_offset_x;

	if (ray->was_hit_vertical)
	{
		texture_offset_x = (int)ray->wall_hit_y % tilesize;
	}
	else
	{
		texture_offset_x = (int)ray->wall_hit_x % tilesize;
	}
	texture_offset_x *= (float)texture->width / tilesize;
	return (texture_offset_x);
}

uint32_t	get_color(t_data *data, int y, t_wall *wall, int texture_offset_x)
{
	int	yh;	
	int	tex_offset_y;

	if (y < wall->top)
	{
		return (data->ceil_color);
	}
	else if (y < wall->bottom)
	{
		yh = y - (WINDOW_HEIGHT / 2) + (wall->height / 2);
		tex_offset_y = (int)((float)yh * wall->texture->height / wall->height);
		return (get_texel_color(wall->texture, texture_offset_x, tex_offset_y));
	}
	else
	{
		return (data->floor_color);
	}
}
