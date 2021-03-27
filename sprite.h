#ifndef SPRITE_H
# define SPRITE_H

#include "graphics.h"

# define NUM_SPRITES 1

typedef struct	s_sprite {
	float x;
	float y;
	float distance;
	float angle;
	int texture;
}	t_sprite;

void render_sprite_projection(void);
void render_map_sprites(void);

#endif
