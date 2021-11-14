#include "map.h"

bool map_has_wall_at(t_map *map, float x, float y)
{
	int map_x_index;
	int map_y_index;

	if (x < 0 || x >= map->num_cols * map->tile_size || \
		y < 0 || y >= map->num_rows * map->tile_size)
		return (false);
	map_x_index = floor(x / map->tile_size);
	map_y_index = floor(y / map->tile_size);
	return (map->grid[map_y_index][map_x_index] == '1');
}

bool is_inside_map(t_map *map, t_fpoint *coord)
{
	return (coord->x >= 0 && (coord->x < map->num_cols * map->tile_size) && \
		coord->y >= 0 && (coord->y < map->num_rows * map->tile_size));
}

int get_content_at(t_map *map, t_fpoint *coord)
{	
	if ((int)coord->y >= map->num_rows || (int)coord->x >= map->num_cols)
		return ('0');
	else
		return (map->grid[(int)coord->y][(int)coord->x]);
}

void	render_map_grid(t_map *map, t_window *window)
{
	int i;
	size_t j;
	t_rect rect;

	i = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < ft_strlen(map->grid[i]))
		{
			// TODO : minimap should be proportional to window, not to tile_size !!
			rect.x = j * map->tile_size * MINIMAP_SCALE_FACTOR;
			rect.y = i * map->tile_size * MINIMAP_SCALE_FACTOR;
			rect.width = ceil(map->tile_size * MINIMAP_SCALE_FACTOR);
			rect.height = ceil(map->tile_size * MINIMAP_SCALE_FACTOR);

			if (map->grid[i][j] == '0')
				rect.color = 0x00AAAAAA;
			else if (map->grid[i][j] == '1')
				rect.color = 0x00123456;
			else
				rect.color = 0xFF000000;

			draw_rectangle(&rect, window->color_buffer);
			j++;
		}
		i++;
	}
}
