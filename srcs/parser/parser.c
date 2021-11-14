/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:11:05 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 20:19:17 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_cub_file(t_data *data, char *file)
{
	int		fd;
	int		ln;
	char	*line;

	fd = open(file, __O_DIRECTORY);
	if (fd != -1)
		exit_on_error(data, "Your .cub file is a directory.");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_on_error(data, strerror(errno));
	ln = get_next_line(fd, &line);
	if (ln == -1)
		exit_on_error(data, "Error reading .cub file.");
	parse_line(data, line);
	while (ln == 1)
	{
		ln = get_next_line(fd, &line);
		if (ln == -1)
			exit_on_error(data, "Error reading .cub file.");
		parse_line(data, line);
	}
	ln = close(fd);
	if (ln == -1)
		exit_on_error(data, "Error while closing .cub file");
}

void	parse_line(t_data *data, char *line)
{
	static bool	is_map_started;
	static bool	is_map_finished;

	if (!is_map_started)
		is_map_started = parse_identifier_line(data, line);
	if (is_map_started && !is_map_finished)
	{
		if (is_blank_line(line))
			is_map_finished = true;
		parse_map_line(data, line);
	}
	else if (is_map_finished && !is_blank_line(line))
		free_line_and_eoe(line, data, "Blank line inside map.");
	return (free(line));
}

// Return true if detect map beginning, false otherwise
bool	parse_identifier_line(t_data *data, char *line)
{
	int				i;
	static int		texture_id;
	static uint8_t	identifiers;

	i = 0;
	while (line[i] && ft_strchr(" \t", line[i]))
		i++;
	if (line[i] == '\0')
		return (false);
	if (line[i] == 'R' && ft_strchr(" \t", line[i + 1]))
		parse_resolution(data, &identifiers, &data->window, line);
	else if (is_texture_identifier(line + i))
		parse_texture(data, &identifiers, &data->textures[texture_id++], line);
	else if (ft_strchr("FC", line[i]) && ft_strchr(" \t", line[i + 1]))
		parse_ceil_floor_color(&identifiers, data, line);
	else if (ft_strchr("10", line[i]))
	{
		if (identifiers != 127)
			free_line_and_eoe(line, data, "An identifier is missing.");
		return (true);
	}
	else
		free_line_and_eoe(line, data, "Unknown identifier detected.");
	return (false);
}

bool	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_strchr(" \t", line[i]))
		i++;
	return (line[i] == '\0');
}
