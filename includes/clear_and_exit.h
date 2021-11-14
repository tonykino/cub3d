/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_exit.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:10:09 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 18:16:48 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAR_AND_EXIT_H
# define CLEAR_AND_EXIT_H

# include <stdio.h>
# include <stdlib.h>

# include "mlx.h"
# include "data_struct.h"
# include "graphics.h"

void	exit_on_error(t_data *data, char *err_msg);
void	cleanup_and_exit(t_data *data, int exit_status);

#endif