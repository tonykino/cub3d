#include "parser.h"

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

void parse_line(t_data *data, char *line)
{
	int i;
	static bool is_map_started;
	static int texture_id = 0;
	static uint8_t identifiers = 0;

	i = 0;
	while(line[i] && ft_strchr(" \t", line[i]))
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return ;
	}
	if (!is_map_started)
	{
		if (line[i] == 'R' && ft_strchr(" \t", line[i + 1]))
		{
			parse_resolution(&identifiers, &data->window, line);
			printf("window.height=%d, window.width=%d\n", data->window.height, data->window.width);
		}
		if (is_texture_identifier(line + i))
		{
			parse_texture(&identifiers, &data->textures[texture_id], line);
			printf("texture n°%d: texture.name='%s', texture.path='%s'\n", texture_id, data->textures[texture_id].name, data->textures[texture_id].path);
			texture_id++;
		}
		if (ft_strchr("FC", line[i]) && ft_strchr(" \t", line[i + 1]))
		{
			parse_color(&identifiers, data, line);
			printf("ceil_color=%#.8X, floor_color=%#.8X\n", data->ceil_color, data->floor_color);
		}
		if (line[i] == '1')
		{
			if(identifiers != 127)
			{
				printf("identifier=%d\n", identifiers);
				clear_and_exit(6, "An identifier is missing before map.");
			}
			is_map_started = true;
			printf("starting map !\nm:%s\n", line);
		}
		else
		{
			//TODO : HANDLE UNKNOWN IDENTIFIER
		}
	}
	else
	{
		if (line[i] == '1')
			printf("m:%s\n", line);
	}
	free(line);
}

bool is_texture_identifier(char *line)
{
	return (
		((!ft_strncmp(line, "NO", 2) 
			|| !ft_strncmp(line, "SO", 2) 
			|| !ft_strncmp(line, "WE", 2) 
			|| !ft_strncmp(line, "EA", 2))
		&& ft_strchr(" \t", line[2])) 
		|| ( *line == 'S' && ft_strchr(" \t", line[1]))
	);
}

void parse_resolution(uint8_t *identifier, t_window *window, char *line)
{
	char **res;
	int width;
	int height;

	// printf("line='%s'\n", line);
	res = ft_split(line, " \t");
	// printf("res[0]='%s', res[1]='%s', res[2]='%s'\n", res[0], res[1], res[2]);
	if (ft_strcmp(res[0], "R") || !is_number(res[1]) || !is_number(res[2]))
	{
		free(res[0]);
		free(res[1]);
		free(res[2]);
		free(res);
		clear_and_exit(5, "Error while parsing resolution.");
	}
	if ((*identifier & 0b00000001) == RESOLUTION)
	{
		free(res[0]);
		free(res[1]);
		free(res[2]);
		free(res);
		clear_and_exit(5, "Several resolution declaration.");
	}
	*identifier += RESOLUTION;
	width = ft_atoi(res[1]);
	height = ft_atoi(res[2]);
	window->width = width;
	window->height = height;
	window->win_img.width = width;
	window->win_img.height = height;
	free(res[0]);
	free(res[1]);
	free(res[2]);
	free(res);
}

void parse_texture(uint8_t *identifier, t_img *texture, char*line)
{
	char **tex;

	// printf("line='%s'\n", line);
	tex = ft_split(line, " \t");
	if (!ft_strncmp(tex[0], "NO", 2))
	{
		if ((*identifier & 0b00000010) == NO_TEXTURE)
		{
			free(tex[0]);
			free(tex[1]);
			free(tex);
			clear_and_exit(5, "Several NO texture declaration.");
		}
		else
		{
			*identifier += NO_TEXTURE;
		}
	}
	else if (!ft_strncmp(tex[0], "SO", 2))
	{
		if ((*identifier & 0b00000100) == SO_TEXTURE)
		{
			free(tex[0]);
			free(tex[1]);
			free(tex);
			clear_and_exit(5, "Several SO texture declaration.");
		}
		else
		{
			*identifier += SO_TEXTURE;
		}
	}
	else if (!ft_strncmp(tex[0], "EA", 2))
	{
		if ((*identifier & 0b00001000) == EA_TEXTURE)
		{
			free(tex[0]);
			free(tex[1]);
			free(tex);
			clear_and_exit(5, "Several EA texture declaration.");
		}
		else
		{
			*identifier += EA_TEXTURE;
		}
	}
	else if (!ft_strncmp(tex[0], "WE", 2))
	{
		if ((*identifier & 0b00010000) == WE_TEXTURE)
		{
			free(tex[0]);
			free(tex[1]);
			free(tex);
			clear_and_exit(5, "Several WE texture declaration.");
		}
		else
		{
			*identifier += WE_TEXTURE;
		}
	}

	// printf("addr='%p' : tex[0]='%s', tex[1]='%s'\n", texture, tex[0], tex[1]);
	texture->name = tex[0];
	texture->path = tex[1];
	// printf("texture->name = '%s', texture->path = '%s'\n", texture->name, texture->path);

	// TODO : try to open file
	// TODO : get width and height from xpm file => not needed, we got it with mlx function !!!! thx to Emma :D
	free(tex);
}

void parse_color(uint8_t *identifier, t_data *data, char *line)
{
	char **colary;
	uint32_t *color;
	// (void) data;
	colary = ft_split(line, " \t,");
	// printf("colary[0]='%s', colary[1]='%s', colary[2]='%s', colary[3]='%s'\n", colary[0], colary[1], colary[2], colary[3]);
	if (!ft_strcmp(colary[0], "C"))
	{
		color = &data->ceil_color;
		if ((*identifier & 0b01000000) == CEIL_COLOR)
		{
			free(colary[0]);
			free(colary[1]);
			free(colary[2]);
			free(colary[3]);
			free(colary);
			clear_and_exit(5, "Several ceil color declaration.");
		}
		else
		{
			*identifier += CEIL_COLOR;
		}
	}
	else
	{
		color = &data->floor_color;
		if ((*identifier & 0b10000000) == FLOOR_COLOR)
		{
			free(colary[0]);
			free(colary[1]);
			free(colary[2]);
			free(colary[3]);
			free(colary);
			clear_and_exit(5, "Several floor color declaration.");
		}
		else
		{
			*identifier += FLOOR_COLOR;
		}
	}
	// TODO handle color < 0 || color > 255 || color != number
	*color = encode_rgb(ft_atoi(colary[1]), ft_atoi(colary[2]), ft_atoi(colary[3]));
	free(colary[0]);
	free(colary[1]);
	free(colary[2]);
	free(colary[3]);
	free(colary);
}
