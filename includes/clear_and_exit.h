/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_exit.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:10:09 by tokino            #+#    #+#             */
/*   Updated: 2021/11/11 19:10:13 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAR_AND_EXIT_H
# define CLEAR_AND_EXIT_H

# include <stdio.h>
# include <stdlib.h>

# include "data_struct.h"

void	clear_and_exit(int err_code, char *err_msg);
void	cleanup_and_exit(t_data *data, int exit_status);

#endif