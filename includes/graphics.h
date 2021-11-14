/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:43:57 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 21:02:13 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <stdbool.h>
# include <stdlib.h>

// # include "mlx.h"
# include "libft.h"
# include "data_struct.h"
# include "graphics_struct.h"

// PUBLIC API
void		draw_rectangle(t_window *window, t_rect *rect);
void		draw_line(t_window *window, t_line *line);
void		draw_pixel(t_window *window, int x, int y, uint32_t color);
void		clear_color_buffer(t_window *window);
void		copy_color_buffer_in_image(t_window *window);

// PRIVATE API
t_ipoint	set_bresenham_steps(t_line *line);
bool		is_transparent(uint32_t color);

#endif
