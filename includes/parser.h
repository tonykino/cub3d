/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:57:37 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 19:12:46 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>

# include "data_struct.h"
# include "clear_and_exit.h"
# include "get_next_line.h"

// PUBLIC API
void	parse_cub_file(t_data *data, char *file);

// PRIVATE API
# define RESOLUTION 1
# define NO_TEXTURE 2
# define SO_TEXTURE 4
# define EA_TEXTURE 8
# define WE_TEXTURE 16
# define CEIL_COLOR 32
# define FLOOR_COLOR 64

void	parse_line(t_data *data, char *line);
bool	parse_identifier_line(t_data *data, char *line);
bool	is_blank_line(char *line);

void	parse_resolution(t_data *data, uint8_t *identifier, \
	t_window *window, char *line);

void	parse_texture(t_data *data, uint8_t *identifier, \
	t_img *texture, char*line);
bool	is_texture_identifier(char *line);
bool	is_duplicated_texture(char **texary, uint8_t *id);

void	parse_ceil_floor_color(uint8_t *identifier, t_data *data, char *line);
bool	is_duplicated_color(char **colary, uint8_t *id);
bool	are_colors_invalid(char **colary);
bool	is_color_valid(char *color);

void	parse_map_line(t_data *data, char *line);
int		copy_old_grid_into_new_one(t_map *map, char **new_grid);
void	free_old_grid(t_map *map);
void	print_map(t_map *map);

void	free_line_and_eoe(char *line, t_data *data, char *err_msg);
int		number_of_splitted_elt(char **ary);
void	free_ary(char **ary);
void	free_ary_line_and_eoe(char **res, char *line, t_data *data, char *emsg);

#endif