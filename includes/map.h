/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:49:03 by tokino            #+#    #+#             */
/*   Updated: 2021/11/13 18:03:31 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdbool.h>
# include "constants.h"
# include "graphics.h"
# include "points_struct.h"

typedef struct s_map {
	int		tile_size;
	int		num_rows;
	int		num_cols;
	char	**grid;
}	t_map;

bool	map_has_wall_at(t_map *map, float x, float y);
int		get_content_at(t_map *map, t_fpoint *coord);
bool	is_inside_map(t_map *map, t_fpoint *coord);
void	render_map_grid(t_map *map, t_window *window);
void	setup_map(t_map *map);

#endif
