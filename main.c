#include "main.h"

void render_scene(t_data *data)
{
	render_wall_projection(
		data->map.tile_size,
		data->player.rotation_angle,
		data->rays,
		data->textures
	);
	// render_sprite_projection(data->sprites, &data->map, &data->player, data->textures, data->rays);
	if (MINIMAP_SCALE_FACTOR)
	{
		render_map_grid(&data->map);
		render_map_rays(&data->player, data->rays);
		render_map_sprites(data->sprites);
		render_map_player(&data->player);
	}

	copy_color_buffer_in_image(&data->window.win_img);
    mlx_put_image_to_window(get_mlx_ptr(), get_win_ptr(), data->window.win_img.mlx_img, 0, 0);
}

void update_scene(t_data *data)
{
	move_player(&data->player, &data->map);
	cast_all_rays(&data->player, data->rays, &data->map);
}

int update_and_render(t_data *data)
{
	if (no_window())
		return 1;
	
	// mlx_clear_window(data->mlx_ptr, data->win_ptr); // Useless ?
	// clear_img(&data->win_img);
	clear_color_buffer(0x00FFFFFF);

	update_scene(data);
	render_scene(data);
	
	return 0;
}

void setup(t_data *data)
{
	setup_map(&data->map);
	setup_player(&data->player, &data->map);
	setup_sprites(data->sprites);
	load_textures(data->textures);
}

void	clear_and_exit(int err_code, char *err_msg)
{
	printf("%s\n", err_msg);
	printf("\n\n---- LEAKS ----\n");
	system("leaks --quiet a.out");
	exit(err_code);
}

bool valid_cub_file_name(char *filename)
{
	int len;

	len = ft_strlen(filename);
	return (!ft_strcmp(filename + len - 4, ".cub"));
}

// t_identifiers get_identifier(char *line)
// {
// 	int i;

// 	i = 0;
// 	while(line[i] && ft_strchr(" \t", line[i]))
// 		i++;
// 	if (line[i] == 'R')
// 		return (R);
// 	if (line[i] == 'N' && line[i + 1] == 'O')
// 		return (NO);
// 	if (line[i] == 'S' && line[i + 1] == 'O')
// 		return (SO);
// 	if (line[i] == 'W' && line[i + 1] == 'E')
// 		return (WE);
// 	if (line[i] == 'E' && line[i + 1] == 'A')
// 		return (EA);
// 	if (line[i] == 'S')
// 		return (NO);
// 	if (line[i] == '1')
// 	clear_and_exit(4, "Unknown identifier (should be R, NO, SO, EA, WE or S).");
// }

void parse_resolution(t_window *window, char *line)
{
	char **res;

	printf("line='%s'\n", line);
	res = ft_split(line, " \t");
	printf("res[0]='%s', res[1]='%s', res[2]='%s'\n", res[0], res[1], res[2]);
	if (ft_strcmp(res[0], "R") || !is_number(res[1]) || !is_number(res[2]))
	{
		clear_and_exit(5, "Error while parsing resolution.");
	}
	window->width = ft_atoi(res[1]);
	window->height = ft_atoi(res[2]);
	free(res[0]);
	free(res[1]);
	free(res[2]);
	free(res);
}

void parse_line(t_data *data, char *line)
{
	int i;
	static bool is_map_started;

	i = 0;
	while(line[i] && ft_strchr(" \t", line[i]))
		i++;
	if (!is_map_started)
	{
		if (line[i] == 'R' && ft_strchr(" \t", line[i + 1]))
		{
			parse_resolution(&data->window, line);
			printf("height=%d, width=%d\n", data->window.height, data->window.width);
		}
		if (line[i] == 'N' && line[i + 1] == 'O' && ft_strchr(" \t", line[i + 2]))
			printf("texture no : %s\n", line);
		if (line[i] == 'S' && line[i + 1] == 'O' && ft_strchr(" \t", line[i + 2]))
			printf("texture so : %s\n", line);
		if (line[i] == 'W' && line[i + 1] == 'E' && ft_strchr(" \t", line[i + 2]))
			printf("texture we : %s\n", line);
		if (line[i] == 'E' && line[i + 1] == 'A' && ft_strchr(" \t", line[i + 2]))
			printf("texture ea : %s\n", line);
		if (line[i] == 'S' && ft_strchr(" \t", line[i + 1]))
			printf("texture s  : %s\n", line);
		if (line[i] == 'F' && ft_strchr(" \t", line[i + 1]))
			printf("color f    : %s\n", line);
		if (line[i] == 'C' && ft_strchr(" \t", line[i + 1]))
			printf("color c    : %s\n", line);
		if (line[i] == '1')
		{
			is_map_started = true;
			printf("starting map !\nm:%s\n", line);
		}
	}
	else
	{
		if (line[i] == '1')
			printf("m:%s\n", line);
	}
	free(line);
	(void) data;
}

void	parse_cub_file(t_data *data, char *file)
{
	int fd;
	int ln;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		clear_and_exit(errno, "Error while opening .cub file.");
	ln = get_next_line(fd, &line);
	if (ln == -1)
		clear_and_exit(3, "Error reading .cub file.");
	parse_line(data, line);
	while(ln == 1)
	{
		ln = get_next_line(fd, &line);
		if (ln == -1)
			clear_and_exit(3, "Error reading .cub file.");
		parse_line(data, line);
	}

	close(fd); // TOFINISH
}

void	init_img(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->path = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
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

void	init_all_data(t_data *data)
{
	init_window(&data->window);
	init_textures(data->textures);
	// init_sprites(data->sprites);
	// init_map(&data->map);
	// init_player(&data->player);
	// init_rays(data->rays);
}

void init_cub3d(t_data *data, int argc, char **argv)
{
	if (argc != 2 && argc != 3)
		clear_and_exit(1, "Invalid number of arguments.");
	if (!valid_cub_file_name(argv[1]))
		clear_and_exit(1, "Invalid map file name.");
	init_all_data(data);
	parse_cub_file(data, argv[1]);
}

int	main(int argc, char **argv)
{
	t_data data;

	// (void) data;
	// (void) argc;
	// (void) argv;
	system("clear && echo ---- Start Cub3D ----");
	init_cub3d(&data, argc, argv);

	// init_mlx_data(&data.window.win_img);
	// setup(&data);
	// mlx_mouse_hook(get_win_ptr(), mouse_hook, 0);
	// mlx_hook(get_win_ptr(), KeyPress, KeyPressMask, &handle_keypress, &data.player);
	// mlx_hook(get_win_ptr(), KeyRelease, KeyReleaseMask, &handle_keyrelease, &data.player);
	// mlx_loop_hook(get_mlx_ptr(), &update_and_render, &data);
	// mlx_loop(get_mlx_ptr());

	// // free_textures();
	// clear_mlx_data(data.win_img.mlx_img);
	printf("\n\n---- LEAKS ----\n");
	system("leaks --quiet a.out");
	return(0);
}

// Pour tester le code :
// gcc -Wall -Werror -Wextra -Llibmlx -Ilibmlx -lmlx -framework OpenGL -framework AppKit main.c && ./a.out
