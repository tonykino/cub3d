#include "map.h"

static const int	grid[13][20] = { \
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} \
	};

bool map_has_wall_at(t_map *map, float x, float y)
{
	int map_x_index;
	int map_y_index;

	if (x < 0 || x >= map->num_cols * map->tile_size || y < 0 || y >= map->num_rows * map->tile_size)
		return (true);
	map_x_index = floor(x / map->tile_size);
	map_y_index = floor(y / map->tile_size);
	return (grid[map_y_index][map_x_index] == 1);
}

bool is_inside_map(t_map *map, int x, int y)
{
	return (x >= 0 && (x < map->num_cols * map->tile_size) && y >= 0 && (y < map->num_rows * map->tile_size));
}

int get_content_at(int x, int y)
{
	return (grid[y][x]);
}

void setup_map(t_map *map)
{
	map->tile_size = 128;
	map->num_rows = 13;
	map->num_cols = 20;
}

void	render_map_grid(t_map *map)
{
	int i;
	int j;
	t_rect rect;

	i = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			rect.x = j * map->tile_size * MINIMAP_SCALE_FACTOR;
			rect.y = i * map->tile_size * MINIMAP_SCALE_FACTOR;
			rect.width = map->tile_size * MINIMAP_SCALE_FACTOR;
			rect.height = map->tile_size * MINIMAP_SCALE_FACTOR;

			if (grid[i][j] == 0)
				rect.color = 0x00AAAAAA;
			else
				rect.color = 0x00123456;

			draw_rectangle(&rect);
			j++;
		}
		i++;
	}
}
