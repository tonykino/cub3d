#include "sprite.h"

void	setup_sprites(t_sprite *sprites)
{
	sprites[0].x = 256;
	sprites[0].y = 256;
	sprites[0].texture = 4;
	sprites[0].visible = false;

	sprites[1].x = 768;
	sprites[1].y = 256;
	sprites[1].texture = 4;
	sprites[1].visible = false;

	sprites[2].x = 768;
	sprites[2].y = 768;
	sprites[2].texture = 4;
	sprites[2].visible = false;

	sprites[3].x = 1024;
	sprites[3].y = 896;
	sprites[3].texture = 4;
	sprites[3].visible = false;

	sprites[4].x = 384;
	sprites[4].y = 1024;
	sprites[4].texture = 4;
	sprites[4].visible = false;
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
		rect.color = (sprites[i].visible) ? 0x0000FFFF : 0x00444444;
		draw_rectangle(&rect);
		i++;
	}
}

void render_sprite_projection(t_sprite *sprites, t_map *map, t_player *player, t_img *textures, t_ray *rays)
{
	t_sprite visible_sprites[NUM_SPRITES];
	int i;
	int num_visible_sprites;
	float angle_sprite_player;

	// GET VISIBLE SPRITES
	i = 0;
	num_visible_sprites = 0;
	while (i < NUM_SPRITES)
	{
		angle_sprite_player = player->rotation_angle - atan2(sprites[i].y - player->y, sprites[i].x - player->x);
		if (angle_sprite_player > M_PI)
			angle_sprite_player -= (M_PI * 2);
		if (angle_sprite_player < - M_PI)
			angle_sprite_player += (M_PI * 2);
		angle_sprite_player = fabs(angle_sprite_player);
		if (angle_sprite_player < (FOV_ANGLE / 2) + 0.2)
		{
			sprites[i].visible = true; // Usefull ?
			sprites[i].angle = angle_sprite_player;
			sprites[i].distance = dist_between_points(sprites[i].x, sprites[i].y, player->x, player->y);
			visible_sprites[num_visible_sprites] = sprites[i];
			num_visible_sprites++;	
		}
		else
		{
			sprites[i].visible = false;
		}
		i++;
	}

	// SORTING SPRITES
	i = 0;
	int j;
	while (i < num_visible_sprites)
	{
		j = i + 1;
		while (j < num_visible_sprites)
		{
			if (visible_sprites[i].distance < visible_sprites[j].distance)
			{
				t_sprite temp = visible_sprites[i];
				visible_sprites[i] = visible_sprites[j];
				visible_sprites[j] = temp;
			}
			j++;
		}
		i++;
	}

	// RENDERING VISIBLE SPRITES
	i = 0;
	while (i < num_visible_sprites)
	{
		t_sprite sprite = visible_sprites[i];

		float sprite_height = (map->tile_size / sprite.distance) * DIST_PROJ_PLANE;
		float sprite_width = sprite_height;
		float sprite_top_y = (WINDOW_HEIGHT / 2) - (sprite_height / 2);
		// if (sprite_top_y < 0)
		// 	sprite_top_y = 0;
		float sprite_bottom_y= (WINDOW_HEIGHT / 2) + (sprite_height / 2);
		// if (sprite_bottom_y > WINDOW_HEIGHT)
		// 	sprite_height = WINDOW_HEIGHT;

		float sprite_angle = atan2(sprite.y - player->y, sprite.x - player->x) - player->rotation_angle;
		float sprite_screen_pos_x = tan(sprite_angle) * DIST_PROJ_PLANE;

		float sprite_left_x = (WINDOW_WIDTH / 2) + sprite_screen_pos_x - (sprite_width / 2);
		float sprite_right_x = sprite_left_x + sprite_width;

		int texture_width = textures[sprite.texture].width;
		int texture_height = textures[sprite.texture].height;

		for (int x = sprite_left_x; x < sprite_right_x; x++)
		{
			int texture_ofset_x = (x - sprite_left_x) * texture_width / sprite_width;
			for (int y = sprite_top_y; y < sprite_bottom_y; y++)
			{
				if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
				{
					int texture_offset_y = (y - sprite_top_y) * ((float)texture_height / sprite_height);
					uint32_t color = get_texel_color(textures + 4, texture_ofset_x, texture_offset_y);
					if (sprite.distance < rays[x].distance)
						draw_pixel(x, y, color);
				}
			}
		}
		
		i++;
	}


}
