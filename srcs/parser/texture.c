/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:05:21 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 13:46:43 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_texture_identifier(char *line)
{
	return (((!ft_strncmp(line, "NO", 2) \
			|| !ft_strncmp(line, "SO", 2) \
			|| !ft_strncmp(line, "WE", 2) \
			|| !ft_strncmp(line, "EA", 2)) \
		&& ft_strchr(" \t", line[2])));
}

void	parse_texture(t_data *data, uint8_t *identifier, \
					t_img *texture, char*line)
{
	char	**texary;

	texary = ft_split(line, " \t");
	if (texary == NULL)
		free_line_and_eoe(line, data, "Error while spliting a texture line");
	if (number_of_splitted_elt(texary) != 2)
		free_ary_line_and_eoe(texary, line, data, "Texture should be 2 elts");
	if (is_duplicated_texture(texary, identifier))
		free_ary_line_and_eoe(texary, line, data, \
			"Duplicated texture declaration.");
	if (!ft_strncmp(texary[0], "NO", 2))
		*identifier += NO_TEXTURE;
	else if (!ft_strncmp(texary[0], "SO", 2))
		*identifier += SO_TEXTURE;
	else if (!ft_strncmp(texary[0], "EA", 2))
		*identifier += EA_TEXTURE;
	else if (!ft_strncmp(texary[0], "WE", 2))
		*identifier += WE_TEXTURE;
	texture->name = texary[0];
	texture->path = texary[1];
	free(texary);
}

bool	is_duplicated_texture(char **texary, uint8_t *id)
{
	return ((!ft_strcmp(texary[0], "NO") && (*id & 0b00000010) == NO_TEXTURE) \
		|| (!ft_strcmp(texary[0], "SO") && (*id & 0b00000100) == SO_TEXTURE) \
		|| (!ft_strcmp(texary[0], "EA") && (*id & 0b00001000) == EA_TEXTURE) \
		|| (!ft_strcmp(texary[0], "WE") && (*id & 0b00010000) == WE_TEXTURE));
}
