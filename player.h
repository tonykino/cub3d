#ifndef PLAYER_H
# define PLAYER_H

# include <stdio.h>
# include <math.h>
# include "graphics.h"
# include "constants.h"
# include "map.h"

typedef struct s_player {
	float x;
	float y;
	float width;
	float height;
	int turn_direction; // -1 for left, +1 for right
	int walk_direction; // -1 for back, +1 for front
	float rotation_angle;
	float walk_speed;
	float turn_speed;
}	t_player;

void render_player(t_player *player);
void move_player(t_player *player, t_map *map);
void setup_player(t_player *player, t_map *map);

#endif
