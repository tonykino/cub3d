/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:11:24 by tokino            #+#    #+#             */
/*   Updated: 2021/11/15 14:47:25 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook.h"

int	handle_keypress(int keycode, t_data *data)
{
	t_player	*player;

	player = &data->player;
	if (keycode == W_Z_KEY_SYM)
		player->walk_direction = 1;
	else if (keycode == S_S_KEY_SYM)
		player->walk_direction = -1;
	else if (keycode == D_D_KEY_SYM)
		player->lateral_direction = 1;
	else if (keycode == A_Q_KEY_SYM)
		player->lateral_direction = -1;
	else if (keycode == ARROW_LEFT_KEY_SYM)
		player->turn_direction = -1;
	else if (keycode == ARROW_RIGHT_KEY_SYM)
		player->turn_direction = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	t_player	*player;

	player = &data->player;
	if (keycode == ESC_KEY_SYM)
		cleanup_and_exit(data, 0);
	else if (keycode == W_Z_KEY_SYM || keycode == S_S_KEY_SYM)
		player->walk_direction = 0;
	else if (keycode == D_D_KEY_SYM || keycode == A_Q_KEY_SYM)
		player->lateral_direction = 0;
	else if (keycode == ARROW_LEFT_KEY_SYM || keycode == ARROW_RIGHT_KEY_SYM)
		player->turn_direction = 0;
	return (0);
}

int	mouse_hook(int button, int x, int y)
{
	(void) button;
	(void) x;
	(void) y;
	return (0);
}

int	redcross(t_data *data)
{
	cleanup_and_exit(data, 0);
	return (0);
}
