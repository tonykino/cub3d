#ifndef SPRITE_H
# define SPRITE_H

# include "graphics.h"
# include "player.h"
# include "texture.h"
# include "ray.h"

# define NUM_SPRITES 5

typedef struct	s_sprite {
	float x;
	float y;
	float distance;
	float angle;
	int texture;
	bool visible;
}	t_sprite;

void render_sprite_projection(t_sprite *sprites, t_map *map, t_player *player, t_img *textures, t_ray *rays);
void render_map_sprites(t_sprite *sprites);
void	setup_sprites(t_sprite *sprites);

#endif
