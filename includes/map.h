#ifndef MAP_H
# define MAP_H

# include <stdbool.h>
# include "constants.h"
# include "graphics.h"
# include "points_struct.h"

typedef struct s_map {
	int tile_size;
	int num_rows;
	int num_cols;
	// int **grid;
}	t_map;

bool map_has_wall_at(t_map *map, float x, float y);
int get_content_at(t_fpoint *coord);
bool is_inside_map(t_map *map, t_fpoint *coord);
void	render_map_grid(t_map *map);
void setup_map(t_map *map);

#endif
