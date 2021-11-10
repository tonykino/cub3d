#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

# include <stdint.h>

# include "constants.h"
# include "texture.h"
# include "map.h"
# include "player.h"
# include "ray.h"

typedef struct s_window
{
	void *mlx_ptr;
	void *win_ptr;
	uint32_t *color_buffer;
	t_img win_img;
	int width;
	int height;
}	t_window;

typedef struct s_data
{
	t_window	window;
	t_img		textures[NUM_TEXTURES];
	t_map 		map;
	t_player	player;
	t_ray		rays[NUM_RAYS];
	uint32_t	ceil_color;
	uint32_t	floor_color;
}	t_data;

#endif