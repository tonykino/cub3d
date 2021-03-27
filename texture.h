#ifndef TEXTURE_H
# define TEXTURE_H

# include <stdint.h>
# include <mlx.h>
# include "struct.h"
# include "graphics.h"

# define NUM_TEXTURES 5

uint32_t get_texel_color(t_img *texture, int x, int y);
void load_textures(t_img *textures);
void free_textures(void);

#endif
