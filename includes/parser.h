#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <errno.h>
# include <unistd.h>

# include "data_struct.h"
# include "clear_and_exit.h"
# include "get_next_line.h"

# define RESOLUTION 1
# define NO_TEXTURE 2
# define SO_TEXTURE 4
# define EA_TEXTURE 8
# define WE_TEXTURE 16
# define S_TEXTURE 32
# define CEIL_COLOR 64
# define FLOOR_COLOR 128

// PUBLIC API
void	parse_cub_file(t_data *data, char *file);

// PRIVATE API
void parse_line(t_data *data, char *line);
bool is_texture_identifier(char *line);
void parse_resolution(uint8_t *identifier, t_window *window, char *line);
void parse_texture(uint8_t *identifier, t_img *texture, char*line);
void parse_color(uint8_t *identifier, t_data *data, char *line);

#endif