/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 16:33:42 by tokino            #+#    #+#             */
/*   Updated: 2021/11/15 16:05:34 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

bool	is_open(t_map *map)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->num_rows)
	{
		col = 0;
		while (col < map->num_cols)
		{
			if (ft_strchr("0NSEW", map->grid[row][col]) && \
				(map_is_open_on_top(map, row, col) || \
				map_is_open_on_bottom(map, row, col) || \
				map_is_open_on_left(map, row, col) || \
				map_is_open_on_right(map, row, col)))
			{
				return (true);
			}
			col++;
		}
		row++;
	}
	return (false);
}

bool	map_is_open_on_left(t_map *map, int row, int col)
{
	return (col == 0 || \
		(col > 0 && ft_strchr("01NSEW", map->grid[row][col - 1]) == NULL));
}

bool	map_is_open_on_right(t_map *map, int row, int col)
{
	return (col == map->num_cols - 1 || (col < map->num_cols - 1 && \
		ft_strchr("01NSEW", map->grid[row][col + 1]) == NULL));
}

bool	map_is_open_on_bottom(t_map *map, int row, int col)
{
	return (row == map->num_rows - 1 || (row < map->num_rows - 1 && \
		ft_strchr("01NSEW", map->grid[row + 1][col]) == NULL));
}

bool	map_is_open_on_top(t_map *map, int row, int col)
{
	return (row == 0 || \
		(row > 0 && ft_strchr("01NSEW", map->grid[row - 1][col]) == NULL));
}
