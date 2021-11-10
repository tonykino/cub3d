#ifndef RAY_H
# define RAY_H

# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include <float.h>
# include "points_struct.h"
# include "constants.h"
# include "map.h"
# include "player.h"

# define HORIZONTAL true
# define VERTICAL false

typedef struct s_ray {
	float angle;
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

typedef struct s_ray_hit {
	bool hit;
	float x;
	float y;
	float hit_dist;
	int wall_content;
}	t_ray_hit;

// PUBLIC API
void cast_all_rays(t_player *player, t_ray *rays, t_map *map);
void render_map_rays(t_map *map, t_player *player, t_ray rays[NUM_RAYS]);

// PRIVATE_API
void cast_ray(t_ray *ray, t_player *player, t_map *map);
void set_facing(t_ray *ray);

#endif
