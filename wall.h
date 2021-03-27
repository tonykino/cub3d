#ifndef WALL_H
# define WALL_H

# include "ray.h"
# include "texture.h"

void	wall_projection(int map_tile_size, float player_rotation_angle, t_ray *rays, t_img *textures);

#endif
