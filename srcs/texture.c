#include "texture.h"

static char* texture_filenames[NUM_TEXTURES] = {
	"./textures/HD/Epic-Soul.xpm",
	"./textures/musee_1.xpm",
	"./textures/HD/dragon.xpm",
	"./textures/HD/peeper.xpm",
};


uint32_t get_texel_color(t_img *texture, int x, int y)
{
	char *pix_addr;
	uint32_t pix_color;
	
	pix_addr = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	pix_color = *(uint32_t*)pix_addr;
	return (pix_color);
}

void load_textures(t_img *textures)
{
	int i;
	i = 0;
	while (i < NUM_TEXTURES)
	{
		textures[i].path = texture_filenames[i];
		textures[i].mlx_img = mlx_xpm_file_to_image(
			get_mlx_ptr(), 
			textures[i].path, 
			&textures[i].width,
			&textures[i].height
		);
		textures[i].addr = mlx_get_data_addr(
							textures[i].mlx_img, 
							&textures[i].bpp,
							&textures[i].line_len, 
							&textures[i].endian
						);
		i++;
	}
	
}

// void free_textures(void)
// {
// 	; // TODO
// }
