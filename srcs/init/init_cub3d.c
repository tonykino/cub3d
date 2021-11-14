/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:42:02 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 17:10:20 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	init_cub3d(t_data *data, int argc, char **argv)
{
	int	eflag;

	init_all_data(data);
	if (argc != 2)
		exit_on_error(data, "Invalid number of arguments. \
			Please only add your map.cub file.");
	if (!valid_cub_file_name(argv[1]))
		exit_on_error(data, "Invalid map file name. \
			Your map should be use .cub extension file.");
	parse_cub_file(data, argv[1]);
	check_map_validity(data);
	setup_player(&data->player, &data->map);
	init_mlx_data(data, &data->window);
	eflag = load_textures(data->textures, &data->window);
	if (eflag == -1)
		exit_on_error(data, "Something went wrong when loading textures");
}

bool	valid_cub_file_name(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	return (!ft_strcmp(filename + len - 4, ".cub"));
}
