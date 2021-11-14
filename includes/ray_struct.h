/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:01:04 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 18:02:16 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_STRUCT_H
# define RAY_STRUCT_H

# include <stdbool.h>

typedef struct s_ray {
	float	angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		wall_hit_content;
	bool	was_hit_vertical;
	bool	is_facing_up;
	bool	is_facing_down;
	bool	is_facing_left;
	bool	is_facing_right;
}	t_ray;

#endif
