/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:43:57 by tokino            #+#    #+#             */
/*   Updated: 2021/11/12 16:19:10 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdint.h>

# include "mlx.h"
# include "constants.h"
# include "libft.h"
# include "points_struct.h"

// PUBLIC API
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

void		draw_rectangle(t_rect *rect, uint32_t *color_buffer);
void		draw_line(t_line *line, uint32_t *color_buffer);
void		draw_pixel(int x, int y, uint32_t color, uint32_t *color_buffer);
void		clear_color_buffer(uint32_t *color_buffer);
void		copy_color_buffer_in_image(t_window *window);
void		init_mlx_data(t_window *window);
bool		no_window(t_window *window);

// PRIVATE API
t_ipoint	set_bresenham_steps(t_line *line);
bool		is_transparent(uint32_t color);

#endif
