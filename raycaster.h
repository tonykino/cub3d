#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include "struct.h"
# include "constants.h"

extern const int map[13][20];

bool map_has_wall_at(t_map *map_p, float x, float y);
void cast_ray(float ray_angle, t_ray *ray, t_player *player, t_map *map);
void cast_all_rays(t_data *data);

#endif
