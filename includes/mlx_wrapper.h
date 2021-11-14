/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:11:24 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 22:52:20 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_WRAPPER_H
# define MLX_WRAPPER_H

# include <stdlib.h>

# include "mlx.h"
# include "data_struct.h"
# include "graphics_struct.h"
# include "clear_and_exit.h"

void	init_mlx_data(t_data *data, t_window *window);
bool	no_window(t_window *window);
void	resize_window_if_needed(t_window *window);

#endif
