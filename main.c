#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <stdbool.h>

#define SCENE_WIDTH 640
#define SCENE_HEIGHT 480

#define SE 1
#define NE 2
#define NO 3
#define SO 4

typedef struct  s_img {
    void	*mlx_img;
    char	*addr;
    int		bpp;
    int		line_len;
    int		endian;
} t_img;

typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
    t_img	img;
} t_data;

typedef struct s_rect {
	int x;
	int y;
	int width;
	int height;
	int color;
} t_rect;

bool pixel_is_out_of_screen(t_img *img, int x, int y)
{
	if (x < 0 || x >= SCENE_WIDTH || y < 0 || y >= SCENE_HEIGHT)
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


void	draw_rectangle(t_img *img, t_rect *rect)
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
    printf("Tape on %d !\n", keycode);
	return (0);
}

int mouse_hook(int button, int x, int y)
{
	printf("Click on %d : %d|%d\n", button, x, y);
	return (0);
}

void	init_data(t_data *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return ;//(1);
    mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCENE_WIDTH, SCENE_HEIGHT, "Test");
	if (mlx->win_ptr == NULL)
	{
		free(mlx->win_ptr);
		return ;//(1);
	}
    mlx->img.mlx_img = mlx_new_image(mlx->mlx_ptr, SCENE_WIDTH, SCENE_HEIGHT);
    mlx->img.addr = mlx_get_data_addr(
						mlx->img.mlx_img, 
						&mlx->img.bpp, 
						&mlx->img.line_len, 
						&mlx->img.endian
					);	
}

void clear_img(t_img *img)
{
	int x;
	int y;

	x = 0;
	while (x < SCENE_WIDTH)
	{	
		y = 0;
		while (y < SCENE_HEIGHT)
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

int calc_color(uint8_t red, uint8_t green, uint8_t blue)
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

int render(t_data *data)
{
	if (data->win_ptr == NULL)
		return 1;
	
	// clear_img(&data->img);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	
	static int dir = SE;
	static uint8_t red = 255;
	static uint8_t green = 0;
	static uint8_t blue = 0;
	static t_rect rect = {40, 40, 1, 1, 0x00FF0000};

	// printf("color = %x\n", rect.color);
	draw_rectangle(&data->img, &rect);
	// rect.color = encode_rgb(red, green, blue);
	rect.color = calc_color(red, green, blue);
	// printf("color = %x\n", rect.color);

	if (rect.y + rect.height > SCENE_HEIGHT)
	{
		if (dir == SE)
			dir = NE;
		else if (dir == SO)
			dir = NO;
	}
	if (rect.y < 0 )
	{
		if (dir == NE)
			dir = SE;
		else if (dir == NO)
			dir = SO;
	}
	if (rect.x + rect.width > SCENE_WIDTH)
	{
		if (dir == NE)
			dir = NO;
		else if (dir == SE)
			dir = SO;
	}
	if (rect.x < 0)
	{
		if (dir == NO)
			dir = NE;
		else if (dir == SO)
			dir = SE;
	}

	if (dir == SE)
	{
		rect.x += 1;
		rect.y += 1;
	}
	else if (dir == NE)
	{
		rect.x += 1;
		rect.y -= 1;
	}
	else if (dir == NO)
	{
		rect.x -= 1;
		rect.y -= 1;
	}
	else if (dir == SO)
	{
		rect.x -= 1;
		rect.y += 1;
	}
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return 0;
}

int             main(void)
{
	t_data mlx;

	init_data(&mlx);
    
	mlx_loop_hook(mlx.mlx_ptr, &render, &mlx);
	mlx_key_hook(mlx.win_ptr, key_hook, 0);
	mlx_mouse_hook(mlx.win_ptr, mouse_hook, 0);

    mlx_loop(mlx.mlx_ptr);

	mlx_destroy_image(mlx.mlx_ptr, mlx.img.mlx_img);

	return(0);
}

// Pour tester le code :
// gcc -Llibmlx -Ilibmlx -lmlx -framework OpenGL -framework AppKit main.c && ./a.out