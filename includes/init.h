/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:13:16 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 19:13:28 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "data_struct.h"
# include "clear_and_exit.h"
# include "parser.h"
# include "graphics_struct.h"
# include "player.h"
# include "mlx_wrapper.h"
# include "texture.h"

// PUBLIC API
void	init_cub3d(t_data *data, int argc, char **argv);

// PRIVATE API
bool	valid_cub_file_name(char *filename);
void	init_all_data(t_data *data);
void	init_window(t_window *window);
void	init_textures(t_img *textures);
void	init_img(t_img *img);
void	init_map(t_map *map);

void	check_map_validity(t_data *data);
bool	is_invalid_char(t_map *map);
bool	is_exactly_one_player(t_map *map);

bool	is_open(t_map *map);
bool	map_is_open_on_left(t_map *map, int row, int col);
bool	map_is_open_on_right(t_map *map, int row, int col);
bool	map_is_open_on_top(t_map *map, int row, int col);
bool	map_is_open_on_bottom(t_map *map, int row, int col);

#endif
