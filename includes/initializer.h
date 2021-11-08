#ifndef INITIALIZER_H
# define INITIALIZER_H

# include "data_struct.h"
# include "clear_and_exit.h"
# include "parser.h"
# include "graphics.h"

// PUBLIC API
void init_cub3d(t_data *data, int argc, char **argv);

// PRIVATE API
bool valid_cub_file_name(char *filename);
void	init_all_data(t_data *data);
void	init_window(t_window *window);
void	init_textures(t_img *textures);
void	init_img(t_img *img);

#endif
