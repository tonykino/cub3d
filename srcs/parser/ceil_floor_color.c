/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil_floor_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:02:22 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 13:49:08 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_ceil_floor_color(uint8_t *identifier, t_data *data, char *line)
{
	char		**ary;
	uint32_t	*color;

	ary = ft_split(line, " \t,");
	if (ary == NULL)
		free_line_and_eoe(line, data, "Error while spliting ceil/floor line.");
	if (number_of_splitted_elt(ary) != 4)
		free_ary_line_and_eoe(ary, line, data, "Ceil/floor should be 4 elts");
	if (is_duplicated_color(ary, identifier))
		free_ary_line_and_eoe(ary, line, data, "Duplicated ceil/floor line");
	if (are_colors_invalid(ary))
		free_ary_line_and_eoe(ary, line, data, "Wrong ceil/floor color params");
	if (!ft_strcmp(ary[0], "C"))
	{
		color = &data->ceil_color;
		*identifier += CEIL_COLOR;
	}
	else
	{
		color = &data->floor_color;
		*identifier += FLOOR_COLOR;
	}
	*color = encode_rgb(ft_atoi(ary[1]), ft_atoi(ary[2]), ft_atoi(ary[3]));
	free_ary(ary);
}

bool	are_colors_invalid(char **colary)
{
	return (!is_color_valid(colary[1]) \
		|| !is_color_valid(colary[2]) \
		|| !is_color_valid(colary[3]));
}

bool	is_color_valid(char *color)
{
	return (ft_isnumber(color) && ft_atoi(color) >= 0 && ft_atoi(color) <= 255);
}

bool	is_duplicated_color(char **colary, uint8_t *id)
{
	return ((!ft_strcmp(colary[0], "C") && (*id & 0b00100000) == CEIL_COLOR) \
		|| (!ft_strcmp(colary[0], "F") && (*id & 0b01000000) == FLOOR_COLOR));
}
