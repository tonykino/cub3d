#ifndef HOOK_H
# define HOOK_H

# include <stdlib.h>
# include <stdio.h>
# include "constants.h"
# include "struct.h"
# include "player.h"

int	handle_keypress(int keycode, t_player *player);
int handle_keyrelease(int keycode, t_player *player);
int mouse_hook(int button, int x, int y);

#endif
