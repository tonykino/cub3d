/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:11:24 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 11:33:07 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook.h"

int	handle_keypress(int keycode, t_player *player)
{
	if (keycode == ARROW_UP_KEY_SYM)
	{
		player->walk_direction = 1;
	}
	else if (keycode == ARROW_DOWN_KEY_SYM)
	{
		player->walk_direction = -1;
	}
	else if (keycode == ARROW_LEFT_KEY_SYM)
	{
		player->turn_direction = -1;
	}
	else if (keycode == ARROW_RIGHT_KEY_SYM)
	{
		player->turn_direction = 1;
	}
	printf("Press %d !\n", keycode);
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	t_player	*player;

	player = &data->player;
	if (keycode == ESC_KEY_SYM)
	{
		cleanup_and_exit(data, 0);
	}
	else if (keycode == ARROW_UP_KEY_SYM)
	{
		player->walk_direction = 0;
	}
	else if (keycode == ARROW_DOWN_KEY_SYM)
	{
		player->walk_direction = 0;
	}
	else if (keycode == ARROW_LEFT_KEY_SYM)
	{
		player->turn_direction = 0;
	}
	else if (keycode == ARROW_RIGHT_KEY_SYM)
	{
		player->turn_direction = 0;
	}
	printf("Release %d !\n", keycode);
	return (0);
}

int	mouse_hook(int button, int x, int y)
{
	printf("Click on %d : %d|%d !\n", button, x, y);
	return (0);
}
