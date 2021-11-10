/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:51:41 by tokino            #+#    #+#             */
/*   Updated: 2021/11/10 15:28:39 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	render_map_player(t_player *player, t_window *window)
{
	t_rect	player_rect;
	t_line	player_line;

	player_rect.x = (player->x - player->width / 2) * MINIMAP_SCALE_FACTOR;
	player_rect.y = (player->y - player->height / 2) * MINIMAP_SCALE_FACTOR;
	player_rect.width = player->width * MINIMAP_SCALE_FACTOR;
	player_rect.height = player->height * MINIMAP_SCALE_FACTOR;
	player_rect.color = 0x00FFFF00;
	draw_rectangle(&player_rect, window->color_buffer);
	player_line.x0 = player->x * MINIMAP_SCALE_FACTOR;
	player_line.y0 = player->y * MINIMAP_SCALE_FACTOR;
	player_line.x1 = (player->x + cos(player->rotation_angle) * 1024) \
		* MINIMAP_SCALE_FACTOR;
	player_line.y1 = (player->y + sin(player->rotation_angle) * 1024) \
		* MINIMAP_SCALE_FACTOR;
	player_line.color = 0x000000FF;
	draw_line(&player_line, window->color_buffer);
}
