/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:14:09 by tokino            #+#    #+#             */
/*   Updated: 2021/11/10 12:17:09 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_H
# define WALL_H

# include "ray.h"
# include "texture.h"

// PUBLIC API
void		render_wall_projection(int map_tile_size, \
	float player_rotation_angle, t_ray *rays, t_img *textures);

// PRIVATE API
typedef struct s_wall {
	int		height;
	int		top;
	int		bottom;
	t_img	*texture;
}	t_wall;

t_wall		set_wall(t_ray *ray, float player_rot_angle, int tilesize);
t_img		*get_wall_texture(t_img *textures, t_ray *ray);
int			set_tex_offset_x(t_img *texture, t_ray *ray, int tilesize);
uint32_t	get_color(int y, t_wall *wall, int texture_offset_x);

#endif
