#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <math.h>

# define ESC_KEY_SYM 53
# define ARROW_LEFT_KEY_SYM 123
# define ARROW_RIGHT_KEY_SYM 124
# define ARROW_DOWN_KEY_SYM 125
# define ARROW_UP_KEY_SYM 126

# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 640

# define MINIMAP_SCALE_FACTOR 0.125

# define FOV_ANGLE (60 * (M_PI / 180))
# define NUM_RAYS WINDOW_WIDTH
# define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))

# define KeyPressMask	(1L<<0)
# define KeyReleaseMask	(1L<<1)
# define KeyPress		2
# define KeyRelease		3

#endif
