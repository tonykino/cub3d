#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>

# include "constants.h"
# include "graphics.h"
# include "hook.h"
# include "libft.h"
# include "ray.h"
# include "struct.h"
# include "texture.h"
# include "map.h"
# include "player.h"
# include "wall.h"
# include "sprite.h"
# include "get_next_line.h"

// typedef enum e_identifiers
// {
// 	R,
// 	NO,
// 	SO,
// 	WE,
// 	EA,
// 	S,
// 	M,
// 	NONE
// }	t_identifiers;

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
	t_sprite	sprites[NUM_SPRITES];
	t_map 		map;
	t_player	player;
	t_ray		rays[NUM_RAYS];
}	t_data;

#endif
