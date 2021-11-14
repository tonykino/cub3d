/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:49:03 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 17:59:14 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdbool.h>
# include <stdint.h>

# include "libft.h"
# include "constants.h"
# include "map_struct.h"
# include "points_struct.h"
# include "graphics.h"


bool	map_has_wall_at(t_map *map, float x, float y);
int		get_content_at(t_map *map, t_fpoint *coord);
bool	is_inside_map(t_map *map, t_fpoint *coord);
void	render_map_grid(t_map *map, t_window *window);

#endif
