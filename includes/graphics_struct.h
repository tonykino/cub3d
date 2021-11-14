/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_struct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:31:49 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 18:02:32 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_STRUCT_H
# define GRAPHICS_STRUCT_H

# include <stdint.h>

# include "points_struct.h"

typedef struct s_img {
	void	*mlx_img;
	char	*addr;
	char	*path;
	char	*name;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	uint32_t	*color_buffer;
	t_img		win_img;
	int			width;
	int			height;
}	t_window;

typedef struct s_rect {
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

typedef struct s_line {
	t_ipoint	a;
	t_ipoint	b;
	int			color;
}	t_line;

#endif
