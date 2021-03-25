#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>
# include <stdlib.h>
# include "constants.h"

typedef struct  s_img {
    void	*mlx_img;
    char	*addr;
    int		bpp;
    int		line_len;
    int		endian;
}	t_img;


typedef struct s_rect {
	int x;
	int y;
	int width;
	int height;
	int color;
}	t_rect;

typedef struct s_line {
	int x0;
	int y0;
	int x1;
	int y1;
	int color;
}	t_line;

typedef struct s_player {
	float x;
	float y;
	float width;
	float height;
	int turn_direction; // -1 for left, +1 for right
	int walk_direction; // -1 for back, +1 for front
	float rotation_angle;
	float walk_speed;
	float turn_speed;
}	t_player;

typedef struct s_map {
	int tile_size;
	int num_rows;
	int num_cols;
}	t_map;

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

typedef struct s_data
{
    void    	*mlx_ptr;
    void    	*win_ptr;
	uint32_t	*color_buffer;
    t_img		img;
	t_map 		map_p;
	t_player	player;
	t_ray		rays[NUM_RAYS];
}	t_data;
#endif
