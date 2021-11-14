/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:51:48 by tokino            #+#    #+#             */
/*   Updated: 2021/11/13 15:27:26 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include <stdint.h>
# include "mlx.h"
# include "graphics.h"
# include "libft.h"
# include "clear_and_exit.h"
# include "data_struct.h"

uint32_t	get_texel_color(t_img *texture, int x, int y);
int			load_textures(t_img *textures, t_window *window);
t_img		*get_texture(t_img *textures, char *name);

#endif
