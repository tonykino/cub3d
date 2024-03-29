/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:14:09 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 20:47:46 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_H
# define WALL_H

# include "data_struct.h"
# include "ray_struct.h"
# include "texture.h"
# include "graphics.h"

// PUBLIC API
void		render_wall_projection(t_data *data);

// PRIVATE API
typedef struct s_wall {
	int		height;
	int		top;
	int		bottom;
	t_img	*texture;
}	t_wall;

t_wall		set_wall(t_ray *ray, float player_rot_angle, int tilesize, \
	t_window *window);
t_img		*get_wall_texture(t_img *textures, t_ray *ray);
int			set_tex_offset_x(t_img *texture, t_ray *ray, int tilesize);
uint32_t	get_color(t_data *data, int y, t_wall *wall, int texture_offset_x);

#endif
