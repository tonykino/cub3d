#ifndef RAY_H
# define RAY_H

# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include <float.h>
# include "struct.h"
# include "constants.h"
# include "map.h"
# include "player.h"

typedef struct s_ray {
	float ray_angle;
	float wall_hit_x;
	float wall_hit_y;
	float distance;
	int wall_hit_content;
	bool was_hit_vertical;
	bool is_facing_up;
	bool is_facing_down;
	bool is_facing_left;
	bool is_facing_right;
}	t_ray;

void cast_ray(float ray_angle, t_ray *ray, t_player *player, t_map *map);
void cast_all_rays(t_player *player, t_ray *rays, t_map *map);
void render_rays(t_player *player, t_ray rays[NUM_RAYS]);

#endif
