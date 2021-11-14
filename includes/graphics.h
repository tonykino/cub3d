/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:43:57 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 18:15:39 by tokino           ###   ########.fr       */
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
void		draw_rectangle(t_rect *rect, uint32_t *color_buffer);
void		draw_line(t_line *line, uint32_t *color_buffer);
void		draw_pixel(int x, int y, uint32_t color, uint32_t *color_buffer);
void		clear_color_buffer(uint32_t *color_buffer);
void		copy_color_buffer_in_image(t_window *window);

// PRIVATE API
t_ipoint	set_bresenham_steps(t_line *line);
bool		is_transparent(uint32_t color);

#endif
