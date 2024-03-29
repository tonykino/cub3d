/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:07:20 by tokino            #+#    #+#             */
/*   Updated: 2021/11/15 15:48:54 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_resolution(t_data *data, uint8_t *id, \
						t_window *window, char *line)
{
	char	**res;
	int		width;
	int		height;

	res = ft_split(line, " \t");
	if (res == NULL)
		free_line_and_eoe(line, data, "Error while spliting resolution line.");
	if (number_of_splitted_elt(res) != 3)
		free_ary_line_and_eoe(res, line, data, "Resolution should be 3 elts.");
	if (ft_strcmp(res[0], "R") || !ft_isnumber(res[1]) || !ft_isnumber(res[2]))
		free_ary_line_and_eoe(res, line, data, "Resolution shoud be numbers.");
	if (is_out_of_range(res[1]) || is_out_of_range(res[2]))
		free_ary_line_and_eoe(res, line, data, \
			"Resolution shoud be in range 1-INT_MAX.");
	if ((*id & 0b00000001) == RESOLUTION)
		free_ary_line_and_eoe(res, line, data, "Declare several resolutions.");
	*id += RESOLUTION;
	width = ft_atoi(res[1]);
	height = ft_atoi(res[2]);
	window->width = width;
	window->height = height;
	window->win_img.width = width;
	window->win_img.height = height;
	free_ary(res);
}

bool	is_out_of_range(char *res)
{
	int	nb;

	nb = ft_atoi(res);
	return (nb < 1 || nb > INT_MAX || ft_strlen(res) > 10);
}
