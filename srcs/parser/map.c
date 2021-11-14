/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:33:51 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 14:23:00 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_map_line(t_data *data, char *line)
{
	int		line_len;
	t_map	*map;
	char	**new_grid;
	int		eflag;

	map = &data->map;
	line_len = ft_strlen(line);
	if (line_len > map->num_cols)
		map->num_cols = line_len;
	map->num_rows++;
	new_grid = ft_calloc(map->num_rows, sizeof(char *));
	if (new_grid == NULL)
		free_line_and_eoe(line, data, "Error while parsing map");
	eflag = copy_old_grid_into_new_one(map, new_grid);
	if (eflag == -1)
		free_line_and_eoe(line, data, "Error while parsing map");
	free_old_grid(map);
	map->grid = new_grid;
	new_grid[map->num_rows - 1] = ft_strndup(line, map->num_cols);
	if (new_grid[map->num_rows - 1] == NULL)
		free_line_and_eoe(line, data, "Error while parsing map");
}

int	copy_old_grid_into_new_one(t_map *map, char **new_grid)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (i < map->num_rows - 1)
		{
			new_grid[i] = ft_strndup(map->grid[i], map->num_cols);
			if (new_grid[i] == NULL)
				return (-1);
			i++;
		}
	}
	return (0);
}

void	free_old_grid(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (i < map->num_rows - 1)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
}

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	printf(" - Map -\nWidth: %d | Height: %d\n", map->num_cols, map->num_rows);
	while (map->grid && i < map->num_rows)
	{
		printf("%s\n", map->grid[i]);
		i++;
	}
	printf("End of map\n\n");
}
