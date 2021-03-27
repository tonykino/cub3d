#include "hook.h"

int	handle_keypress(int keycode, t_player *player)
{
	if (keycode == ARROW_UP_KEY_SYM)
	{
		player->walk_direction = 1;
		printf("HERE");
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

int handle_keyrelease(int keycode, t_player *player)
{
	if (keycode == ESC_KEY_SYM)
	{
		printf("Exit !\n");
		exit(0);
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

int mouse_hook(int button, int x, int y)
{
	printf("Click on %d : %d|%d !\n", button, x, y);
	return (0);
}
