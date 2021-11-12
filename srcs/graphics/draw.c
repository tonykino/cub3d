/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:42:50 by tokino            #+#    #+#             */
/*   Updated: 2021/11/12 15:47:31 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_rectangle(t_rect *rect, uint32_t *color_buffer)
{
	int	x;
	int	y;

	x = rect->x;
	while (x < rect->x + rect->width)
	{
		y = rect->y;
		while (y < rect->y + rect->height)
		{
			draw_pixel(x, y, rect->color, color_buffer);
			y++;
		}
		x++;
	}
}

t_ipoint	set_bresenham_steps(t_line *line)
{
	t_ipoint	steps;

	if (line->a.x < line->b.x)
		steps.x = 1;
	else
		steps.x = -1;
	if (line->a.y < line->b.y)
		steps.y = 1;
	else
		steps.y = -1;
	return (steps);
}

void	draw_line(t_line *line, uint32_t *color_buffer)
{
	t_ipoint	delta;
	t_ipoint	steps;
	int			err;
	int			e2;

	delta.x = abs(line->b.x - line->a.x);
	delta.y = -abs(line->b.y - line->a.y);
	steps = set_bresenham_steps(line);
	err = delta.x + delta.y;
	draw_pixel(line->a.x, line->a.y, line->color, color_buffer);
	while (line->a.x != line->b.x || line->a.y != line->b.y)
	{
		e2 = 2 * err;
		if (e2 >= delta.y)
		{
			err += delta.y;
			line->a.x += steps.x;
		}
		if (e2 <= delta.x)
		{
			err += delta.x;
			line->a.y += steps.y;
		}
		draw_pixel(line->a.x, line->a.y, line->color, color_buffer);
	}
}
