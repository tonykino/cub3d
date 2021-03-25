#include "main.h"

const int map[13][20] = { \
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} \
	};

bool pixel_is_out_of_screen(t_img *img, int x, int y)
{
	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

	if (pixel_is_out_of_screen(img, x, y))
		return ;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int*)pixel = color;
}


void	render_rectangle(t_img *img, t_rect *rect)
{
	int x;
	int y;

	x = rect->x;
	while(x < rect->x + rect->width)
	{
		y = rect->y;
		while(y < rect->y + rect->height)
		{
			img_pixel_put(img, x, y, rect->color);
			y++;
		}
		x++;
	}
}

int	key_hook(int keycode)
{
	if (keycode == 53)
	{
		printf("Exit !\n");
		exit(0);
	}
    printf("Tap on %d !\n", keycode);
	return (0);
}

int mouse_hook(int button, int x, int y)
{
	printf("Click on %d : %d|%d !\n", button, x, y);
	return (0);
}

void	init_data(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return ;//(1);
    data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Test");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return ;//(1);
	}
    data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    data->img.addr = mlx_get_data_addr(
						data->img.mlx_img, 
						&data->img.bpp, 
						&data->img.line_len, 
						&data->img.endian
					);	
}

void clear_img(t_img *img)
{
	int x;
	int y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{	
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			img_pixel_put(img, x, y, 0x000000);
			y++;
		}
		x++;
	}
}

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	// printf("red = %d, green = %d, blue = %d\n", red, green, blue);
	return (red << 16 | green << 8 | blue);
}

int get_next_rainbow_color(uint8_t red, uint8_t green, uint8_t blue)
{
	static int x = 0;
	if(x>=0 && x<255){
		red = 255;
		green = x;
		blue = 0;
	}
	if(x>=255 && x<510){
		red = 510-x;
		green = 255;
		blue = 0;
	}
	if(x>=510 && x<765){
		red = 0;
		green = 255;
		blue = x-510;
	}
	if(x>=765 && x<1020){
		red = 0;
		green = 1020-x;
		blue = 255;
	}
	if(x>=1020 && x<1275){
		red = x-1020;
		green = 0;
		blue = 255;
	}
	if(x>=1275 && x<=1530){
		red = 255;
		green = 0;
		blue = 1530-x;
	}
	x += 1;
	if (x > 1530)
		x = 0;
	return (encode_rgb(red, green, blue));
}

void render_map(t_img *img, t_map *map_p)
{
	int i;
	int j;
	t_rect rect;

	i = 0;
	while (i < map_p->num_rows)
	{
		j = 0;
		while (j < map_p->num_cols)
		{
			rect.x = j * map_p->tile_size;
			rect.y = i * map_p->tile_size;
			rect.width = map_p->tile_size;
			rect.height = map_p->tile_size;

			if (map[i][j] == 0)
				rect.color = 0x00AAAAAA;
			else
				rect.color = 0x00123456;

			render_rectangle(img, &rect);

			j++;
		}
		i++;
	}
}

int render(t_data *data)
{
	if (data->win_ptr == NULL)
		return 1;
	
	// mlx_clear_window(data->mlx_ptr, data->win_ptr); // Useless ?
	// clear_img(&data->img);

	// t_rect rect = {40, 40, 40, 40, 0x00FFFF00 };
	// render_rectangle(&data->img, &rect);

	render_map(&data->img, &data->map_p);
	// render_rays();
	// render_player();
	
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return 0;
}

void setup_player(t_player *player)
{
	player->x = WINDOW_WIDTH / 2;
	player->y = WINDOW_HEIGHT / 2;
	player->width = 5;
	player->height = 5;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = M_PI_2;
	player->walk_speed = 2;
	player->turn_speed = 9 * (M_PI / 180);
}

void setup_map(t_map *map_p)
{
	map_p->tile_size = 32;
	map_p->num_rows = 13;
	map_p->num_cols = 20;
}

void setup(t_data *data)
{
	setup_player(&data->player);
	setup_map(&data->map_p);
}

int             main(void)
{
	t_data data;

	init_data(&data);
    setup(&data);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_key_hook(data.win_ptr, key_hook, 0);
	mlx_mouse_hook(data.win_ptr, mouse_hook, 0);

    mlx_loop(data.mlx_ptr);

	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);

	return(0);
}

// Pour tester le code :
// gcc -Llibmlx -Ilibmlx -lmlx -framework OpenGL -framework AppKit main.c && ./a.out