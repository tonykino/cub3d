#include "wall.h"

void	wall_projection(int map_tile_size, float player_rotation_angle, t_ray *rays, t_img *textures)
{
	int			x;
	int			y;
	float		projected_wall_height;
	float		corrected_distance;
	int			wall_top_pixel;
	int			wall_bottom_pixel;
	int			texture_offset_x;
	int			texture_offset_y;
	t_img		*texture;
	uint32_t	color;

	x = 0;
	while (x < NUM_RAYS)
	{
		corrected_distance = rays[x].distance * cos(rays[x].ray_angle - player_rotation_angle);
		projected_wall_height = (map_tile_size / corrected_distance) * DIST_PROJ_PLANE;

		wall_top_pixel = (WINDOW_HEIGHT / 2) - ((int)projected_wall_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;

		wall_bottom_pixel = wall_top_pixel + (int)projected_wall_height;
		if (wall_bottom_pixel >= WINDOW_HEIGHT)
			wall_bottom_pixel = WINDOW_HEIGHT - 1;

		if (rays[x].was_hit_vertical)
		{
			texture_offset_x = (int)rays[x].wall_hit_y % map_tile_size;
			if (rays[x].is_facing_right)
				texture = textures + 0;
			else
				texture = textures + 1;
		}
		else
		{
			texture_offset_x = (int)rays[x].wall_hit_x % map_tile_size;
			if (rays[x].is_facing_up)
				texture = textures + 2;
			else
				texture = textures + 3;
		}
		texture_offset_x *= (float)texture->width / map_tile_size;

		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			if (y < wall_top_pixel)
			{
				color = 0x0087CEEB;
			}
			else if (y < wall_bottom_pixel)
			{
				texture_offset_y = (int)((float)(y - (WINDOW_HEIGHT / 2) + ((int)projected_wall_height / 2)) * texture->height / projected_wall_height);
				color = get_texel_color(texture, texture_offset_x, texture_offset_y);
			}
			else 
			{
				color = 0x008B5A2B;
			}
			draw_pixel(x, y, color);
			y++;
		}
		x++;
	}
}
