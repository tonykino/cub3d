#ifndef TEXTURE_H
# define TEXTURE_H

# include <stdint.h>
# include <mlx.h>
# include "struct.h"

# define NUM_TEXTURES 4

uint32_t get_texel_color(t_img *texture, int x, int y);
void load_textures(t_img *textures, t_data *data);
void free_textures(void);

#endif
