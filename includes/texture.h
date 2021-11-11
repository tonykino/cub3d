/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:51:48 by tokino            #+#    #+#             */
/*   Updated: 2021/11/10 16:05:52 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include <stdint.h>
# include "mlx.h"
# include "graphics.h"

# define NUM_TEXTURES 4

uint32_t	get_texel_color(t_img *texture, int x, int y);
void		load_textures(t_img *textures, t_window *window);
void		free_textures(void);

#endif
