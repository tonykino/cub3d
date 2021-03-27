#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>

# include "constants.h"
# include "graphics.h"
# include "hook.h"
# include "libft.h"
# include "ray.h"
# include "struct.h"
# include "texture.h"
# include "map.h"
# include "player.h"

typedef struct s_data
{
	t_img		textures[4];
    t_img		win_img;
	t_map 		map;
	t_player	player;
	t_ray		rays[NUM_RAYS];
}	t_data;

#endif
