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

typedef struct s_data
{
    void    	*mlx_ptr;
    void    	*win_ptr;
    t_img		img;
	t_map 		map_p;
	t_player	player;
}	t_data;
