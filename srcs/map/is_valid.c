/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 15:17:11 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 16:36:49 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	check_map_validity(t_data *data)
{
	t_map	*map;

	map = &data->map;
	if (is_open(map))
		exit_on_error(data, "Map should be closed.");
	if (is_invalid_char(map))
		exit_on_error(data, "Map should only contains 0, 1, space and player.");
	if (!is_exactly_one_player(map))
		exit_on_error(data, "Map should have exactly one player.");
}

bool	is_invalid_char(t_map *map)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->num_rows)
	{
		col = 0;
		while (col < map->num_cols)
		{
			if (ft_strchr("01NSEW ", map->grid[row][col]) == NULL \
				&& map->grid[row][col] != '\0')
				return (true);
			col++;
		}
		row++;
	}
	return (false);
}

bool	is_exactly_one_player(t_map *map)
{
	int	row;
	int	col;
	int	found_player;

	row = 0;
	found_player = 0;
	while (row < map->num_rows)
	{
		col = 0;
		while (col < map->num_cols)
		{
			if (ft_strchr("NSEW", map->grid[row][col]))
				found_player++;
			col++;
		}
		row++;
	}
	return (found_player == 1);
}
