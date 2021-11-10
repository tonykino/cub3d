#include "initializer.h"

void init_cub3d(t_data *data, int argc, char **argv)
{
	if (argc != 2 && argc != 3)
		clear_and_exit(1, "Invalid number of arguments.");
	if (!valid_cub_file_name(argv[1]))
		clear_and_exit(1, "Invalid map file name.");
	init_all_data(data);
	parse_cub_file(data, argv[1]);
	init_mlx_data(&data->window.win_img);
}

bool valid_cub_file_name(char *filename)
{
	int len;

	len = ft_strlen(filename);
	return (!ft_strcmp(filename + len - 4, ".cub"));
}

void	init_all_data(t_data *data)
{
	init_window(&data->window);
	init_textures(data->textures);
	// init_map(&data->map);
	// init_player(&data->player);
	// init_rays(data->rays);
}

void	init_window(t_window *window)
{
	window->mlx_ptr = NULL;
	window->win_ptr = NULL;
	window->color_buffer = NULL;
	init_img(&window->win_img);
	window->width = 0;
	window->height = 0;
}

void	init_textures(t_img *textures)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		init_img(textures + i);
		i++;
	}
}

void	init_img(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->path = NULL;
	img->name = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}
