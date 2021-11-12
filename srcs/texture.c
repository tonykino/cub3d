/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:22:53 by tokino            #+#    #+#             */
/*   Updated: 2021/11/12 22:24:54 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

uint32_t	get_texel_color(t_img *texture, int x, int y)
{
	char		*pix_addr;
	uint32_t	pix_color;

	pix_addr = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	pix_color = *(uint32_t *)pix_addr;
	return (pix_color);
}

void	load_textures(t_img *textures, t_window *window)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		textures[i].mlx_img = mlx_xpm_file_to_image(
				window->mlx_ptr,
				textures[i].path,
				&textures[i].width,
				&textures[i].height
				);
		textures[i].addr = mlx_get_data_addr(
				textures[i].mlx_img,
				&textures[i].bpp,
				&textures[i].line_len,
				&textures[i].endian
				);
		i++;
	}
}

t_img	*get_texture(t_img *textures, char *name)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		if (!ft_strncmp(textures[i].name, name, 2))
		{
			return (textures + i);
		}
		i++;
	}
	return (NULL);
}
