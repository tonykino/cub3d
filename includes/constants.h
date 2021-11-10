/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:46:41 by tokino            #+#    #+#             */
/*   Updated: 2021/11/10 15:47:05 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <math.h>

// MACOS
// # define ESC_KEY_SYM 53
// # define ARROW_LEFT_KEY_SYM 123
// # define ARROW_RIGHT_KEY_SYM 124
// # define ARROW_DOWN_KEY_SYM 125
// # define ARROW_UP_KEY_SYM 126

# define ESC_KEY_SYM 65307
# define ARROW_LEFT_KEY_SYM 65361
# define ARROW_RIGHT_KEY_SYM 65363
# define ARROW_DOWN_KEY_SYM 65364
# define ARROW_UP_KEY_SYM 65362

# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 640

# define MINIMAP_SCALE_FACTOR 0.0125
# define MAX_VIEW_DISTANCE 16.0

# define NUM_RAYS WINDOW_WIDTH
# define FOV_ANGLE (60 * (M_PI / 180))
# define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))

# define COLOR_RED 0x00FF0000
# define COLOR_PURPLE 0x00FF00FF
# define BLACK_COLOR 0x00FFFFFF

#endif
