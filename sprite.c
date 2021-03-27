#include "sprite.h"

void	setup_sprites(t_sprite *sprites)
{
	sprites[0].x = 192;
	sprites[0].y = 192;
	sprites[0].texture = 4;
}

void render_map_sprites(t_sprite *sprites)
{
	int i;
	t_rect rect;

	i = 0;
	while (i < NUM_SPRITES)
	{
		rect.x = sprites[i].x * MINIMAP_SCALE_FACTOR;
		rect.y = sprites[i].y * MINIMAP_SCALE_FACTOR;
		rect.width = 3;
		rect.height = 3;
		rect.color = 0x0000FFFF;
		draw_rectangle(&rect);
		i++;
	}
}

void render_sprite_projection(void)
{

}
